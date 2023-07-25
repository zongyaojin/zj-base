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

    m_overtimeCount = 0;
    m_overtimeCountLimit = overtimeCountLimit;
    m_totalOvertimeCount = 0;

    m_period = ZjChrono::Ns {static_cast<ZjChrono::Count>(1.0 / frequency)};
}

bool ZjTimer::guard()
{
    m_timeSpent = std::chrono::duration_cast<ZjChrono::Ns>(ZjChrono::Clock::now() - m_startTime);
    m_timeLeft = m_period - m_timeSpent;

    if (m_timeLeft.count() < 0) {
        m_overtimeCount++;
        m_totalOvertimeCount++;
    } else {
        std::this_thread::sleep_for(m_timeLeft);
        m_overtimeCount = 0;
    }

    m_totalTimeSpent += m_timeSpent.count();
    m_totalCount++;

    if (m_overtimeCountLimit == 0) {
        return true;
    }

    if (m_overtimeCount > m_overtimeCountLimit) {
        auto&& loopAvgMs = (m_totalTimeSpent / m_totalCount) * ZjChrono::s_nsToMs;
        auto&& periodMs = m_period.count() * ZjChrono::s_nsToMs;
        _ZJ_WARN("[{}] ========== ==========", m_name);
        _ZJ_WARN("-- overtime count [{}] exceeds limit [{}]", m_overtimeCount, m_overtimeCountLimit);
        _ZJ_WARN("-- loop average [{:.3f} ms], expected period  [{:.3f} ms]", loopAvgMs, periodMs);
        m_overtimeCount = 0;
        return false;
    }

    return true;
}

double ZjTimer::getLoopAvg(const Unit unit) const
{
    switch (unit) {
        case Unit::Sec:
            return (m_totalTimeSpent / m_totalCount) * ZjChrono::s_nsToSec;
        case Unit::Ms:
            return (m_totalTimeSpent / m_totalCount) * ZjChrono::s_nsToMs;
        case Unit::Us:
            return (m_totalTimeSpent / m_totalCount) * ZjChrono::s_nsToUs;
        case Unit::Ns:
            return static_cast<double>(m_totalTimeSpent / m_totalCount);
        default:
            return 0.0;
    }
}
