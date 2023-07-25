#include "ZjTimer.hpp"
#include "ZjLogMacrosExtension.hpp"

#include <thread>

ZjTimer::ZjTimer(const std::string name)
{
    if (!name.empty()) {
        m_name = fmt::format("ZjTimer-{}", name);
    }
}

void ZjTimer::init(const unsigned frequency, const unsigned overtimeCountLimit)
{
    m_totalCount = 0;
    m_totalTimeSpent = 0;

    m_overtimeCountLimit = overtimeCountLimit;
    m_overtimeCount = 0;

    m_period = ZjChrono::Ns {static_cast<ZjChrono::Count>(ZjChrono::s_secToNs / frequency)};
}

void ZjTimer::guard()
{
    m_totalCount++;

    m_timeSpent = std::chrono::duration_cast<ZjChrono::Ns>(ZjChrono::Clock::now() - m_startTime);
    m_totalTimeSpent += m_timeSpent.count();
    m_timeLeft = m_period - m_timeSpent;

    if (m_timeLeft.count() > 0) [[likely]] {
        std::this_thread::sleep_for(m_timeLeft);
    } else if (m_timeLeft.count() < 0) [[unlikely]] {
        m_overtimeCount++;
    }

    if (m_overtimeCountLimit > 0 && m_overtimeCount > m_overtimeCountLimit) [[unlikely]] {
        auto&& loopAvgMs = static_cast<double>(m_totalTimeSpent) / m_totalCount * ZjChrono::s_nsToMs;
        auto&& periodMs = m_period.count() * ZjChrono::s_nsToMs;
        _ZJ_WARN("[{}] ========== ==========", m_name);
        _ZJ_WARN("-- overtime count [{}] exceeds limit [{}]", m_overtimeCount, m_overtimeCountLimit);
        _ZJ_WARN("-- loop average [{:.3f} ms], expected period  [{:.3f} ms]", loopAvgMs, periodMs);
        _ZJ_WARN("-- overtime count has been reset to start over");
        m_overtimeCount = 0;
    }
}

double ZjTimer::loopAvg(const ZjChrono::Unit unit) const
{
    switch (unit) {
        case ZjChrono::Unit::Sec:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * ZjChrono::s_nsToSec;
        case ZjChrono::Unit::Ms:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * ZjChrono::s_nsToMs;
        case ZjChrono::Unit::Us:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * ZjChrono::s_nsToUs;
        case ZjChrono::Unit::Ns:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount;
        default:
            return 0.0;
    }
}

double ZjTimer::period(const ZjChrono::Unit unit) const
{
    switch (unit) {
        case ZjChrono::Unit::Sec:
            return m_period.count() * ZjChrono::s_nsToSec;
        case ZjChrono::Unit::Ms:
            return m_period.count() * ZjChrono::s_nsToMs;
        case ZjChrono::Unit::Us:
            return m_period.count() * ZjChrono::s_nsToUs;
        case ZjChrono::Unit::Ns:
            return m_period.count();
        default:
            return 0.0;
    }
}
