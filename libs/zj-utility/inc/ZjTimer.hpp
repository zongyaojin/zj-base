/**
 * @file ZjTimer.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-debug.hpp"
#include "zj-chrono.hpp"

#include <string>

#include "fmt/format.h"

class ZjTimer
{
public:
    explicit ZjTimer(const std::string& name = "");
    ~ZjTimer() = default;

    /**
     * @brief Initialize the timer
     *
     * @param frequency Desired running frequency
     * @param overtimeCountLimit  The limit of overtime count; if 0 is used, they loop running over time won't trigger anything; otherwise,
     * it will trigger designed behaviors in the implementation
     */
    void init(const unsigned frequency, const unsigned overtimeCountLimit = 0);

    /// Start time a loop
    inline void start() { m_startTime = ZjChronoClock::now(); }

    /// Get count since start in Ns, can be used to time a segment
    inline ZjChronoCount sinceStart() const
    {
        return std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - m_startTime).count();
    }

    /**
     * @brief Guard the loop, if time spent since start is less than specified period (via frequency), it will speed until then; otherwise
     * it will issue warning
     *
     * @return ZjChronoCount Number count since start
     */
    ZjChronoCount guard();

    /// Loop period
    double period(const ZjChronoUnit unit) const;

    /// Overtime count of the last loop
    inline ZjChronoCount overtimeCount() const { return m_overtimeCount; }

    /// Timer name
    inline const std::string& name() const { return m_name; }

    /// Total number of counts of all cycles
    inline ZjChronoCount totalCount() const { return m_totalCount; }

    /// Total loop average of all cycles
    double totalLoopAvg(const ZjChronoUnit unit) const;

private:
    std::string m_name {fmt::format("ZjTimer-{}", fmt::ptr(this))};

    ZjChronoCount m_overtimeCount {0};
    ZjChronoCount m_overtimeCountLimit {0};

    ZjChronoNs m_period {0};
    ZjChronoTimePoint m_startTime {ZjChronoClock::now()};
    ZjChronoNs m_timeSpent {0};
    ZjChronoNs m_timeLeft {0};

    ZjChronoCount m_totalCount {0};
    ZjChronoCount m_totalTimeSpent {0};
};
