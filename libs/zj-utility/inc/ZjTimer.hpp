#pragma once

#include "ZjDebug.hpp"
#include "ZjChrono.hpp"

#include "fmt/format.h"

class ZjTimer
{
public:
    ZjTimer(const std::string name = "");
    ~ZjTimer() = default;

    void init(const unsigned frequency, const unsigned overtimeCountLimit = 0);

    inline void start() { m_startTime = ZjChrono::Clock::now(); }

    /// Get count in Ns since start, can be used for timing a segment
    inline ZjChrono::Count sinceStart() const
    {
        return std::chrono::duration_cast<ZjChrono::Ns>(ZjChrono::Clock::now() - m_startTime).count();
    }

    /// Returns the count at the beginning of this function
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