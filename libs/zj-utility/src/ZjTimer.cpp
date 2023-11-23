/**
 * @file ZjTimer.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "ZjTimer.hpp"
#include "zj-logging-macros-simplified.hpp"

#include <thread>

ZjTimer::ZjTimer(const std::string& name)
{
    if (!name.empty()) {
        m_name = fmt::format("ZjTimer-{}", name);
    }
}

void ZjTimer::Init(const unsigned frequency, const unsigned overtimeCountLimit)
{
    m_totalCount = 0;
    m_totalTimeSpent = 0;

    m_overtimeCountLimit = overtimeCountLimit;
    m_overtimeCount = 0;

    m_period = ZjChronoNs {static_cast<ZjChronoCount>(zj::kSecToNs / frequency)};
}

ZjChronoCount ZjTimer::guard()
{
    m_totalCount++;

    m_timeSpent = std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - m_startTime);
    m_totalTimeSpent += m_timeSpent.count();
    m_timeLeft = m_period - m_timeSpent;

    if (m_timeLeft.count() > 0) [[likely]] {
        std::this_thread::sleep_for(m_timeLeft);
    } else if (m_timeLeft.count() < 0) [[unlikely]] {
        m_overtimeCount++;
    }

    // There should be an [[unlikely]] here, but the current version of cpplint doesn't get it
    if (m_overtimeCountLimit > 0 && m_overtimeCount > m_overtimeCountLimit) {
        auto&& loopAvgMs = static_cast<double>(m_totalTimeSpent) / m_totalCount * zj::kNsToMs;
        auto&& periodMs = m_period.count() * zj::kNsToMs;
        _ZJ_WARN("[{}] ========== ==========", m_name);
        _ZJ_WARN("-- overtime count [{}] exceeds limit [{}]", m_overtimeCount, m_overtimeCountLimit);
        _ZJ_WARN("-- loop average [{:.3f} ms], expected period  [{:.3f} ms]", loopAvgMs, periodMs);
        _ZJ_WARN("-- overtime count has been reset to start over");
        m_overtimeCount = 0;
    }

    return m_timeSpent.count();
}

double ZjTimer::totalLoopAvg(const ZjChronoUnit unit) const
{
    switch (unit) {
        case ZjChronoUnit::kSec:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * zj::kNsToSec;
        case ZjChronoUnit::kMs:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * zj::kNsToMs;
        case ZjChronoUnit::kUs:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount * zj::kNsToUs;
        case ZjChronoUnit::kNs:
            return static_cast<double>(m_totalTimeSpent) / m_totalCount;
        default:
            return 0.0;
    }
}

double ZjTimer::period(const ZjChronoUnit unit) const
{
    switch (unit) {
        case ZjChronoUnit::kSec:
            return m_period.count() * zj::kNsToSec;
        case ZjChronoUnit::kMs:
            return m_period.count() * zj::kNsToMs;
        case ZjChronoUnit::kUs:
            return m_period.count() * zj::kNsToUs;
        case ZjChronoUnit::kNs:
            return m_period.count();
        default:
            return 0.0;
    }
}
