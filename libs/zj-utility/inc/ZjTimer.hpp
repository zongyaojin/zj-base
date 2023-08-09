/**
 * @file ZjTimer.hpp
 *
 * @brief Timer class
 *
 * @author Zongyao Jin
 * @date 2023-08-08
 */

#pragma once

#include "ZjDebug.hpp"
#include "ZjChrono.hpp"

#include "fmt/format.h"

class ZjTimer
{
public:
    ZjTimer(const std::string name = "");
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
    inline void start() { m_startTime = ZjChrono::Clock::now(); }

    /// Get count since start in Ns, can be used to time a segment
    inline ZjChrono::Count sinceStart() const
    {
        return std::chrono::duration_cast<ZjChrono::Ns>(ZjChrono::Clock::now() - m_startTime).count();
    }

    /**
     * @brief Guard the loop, if time spent since start is less than specified period (via frequency), it will speed until then; otherwise
     * it will issue warning
     *
     * @return ZjChrono::Count Number count since start
     */
    ZjChrono::Count guard();

    /// Loop period
    double period(const ZjChrono::Unit unit) const;

    /// Overtime count of the last loop
    inline ZjChrono::Count overtimeCount() const { return m_overtimeCount; }

    /// Timer name
    inline const std::string& name() const { return m_name; }

    /// Total number of counts of all cycles
    inline ZjChrono::Count totalCount() const { return m_totalCount; };

    /// Total loop average of all cycles
    double totalLoopAvg(const ZjChrono::Unit unit) const;

private:
    std::string m_name {fmt::format("ZjTimer-{}", fmt::ptr(this))};

    ZjChrono::Count m_overtimeCount {0};
    ZjChrono::Count m_overtimeCountLimit {0};

    ZjChrono::Ns m_period {0};
    ZjChrono::TimePoint m_startTime {ZjChrono::Clock::now()};
    ZjChrono::Ns m_timeSpent {0};
    ZjChrono::Ns m_timeLeft {0};

    ZjChrono::Count m_totalCount {0};
    ZjChrono::Count m_totalTimeSpent {0};
};