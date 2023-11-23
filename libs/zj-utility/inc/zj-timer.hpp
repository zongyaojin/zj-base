/**
 * @file zj-timer.hpp
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
     * @param overtime_count_limit  The limit of overtime count; if 0 is used, they loop running over time won't trigger anything;
     * otherwise, it will trigger designed behaviors in the implementation
     */
    void Init(const unsigned frequency, const unsigned overtime_count_limit = 0);

    /// Start time a loop
    inline void Start() { start_time_ = ZjChronoClock::now(); }

    /// Get count since start in Ns, can be used to time a segment
    inline ZjChronoCount SinceStart() const { return std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - start_time_).count(); }

    /**
     * @brief Guard the loop, if time spent since start is less than specified period (via frequency), it will speed until then; otherwise
     * it will issue warning
     *
     * @return ZjChronoCount Number count since start
     */
    ZjChronoCount Guard();

    /// Loop period
    double Period(const ZjChronoUnit unit) const;

    /// Overtime count of the last loop
    inline ZjChronoCount OvertimeCount() const { return overtime_count_; }

    /// Timer name
    inline const std::string& Name() const { return name_; }

    /// Total number of counts of all cycles
    inline ZjChronoCount TotalCount() const { return total_count_; }

    /// Total loop average of all cycles
    double TotalLoopAverage(const ZjChronoUnit unit) const;

private:
    std::string name_ {fmt::format("ZjTimer-{}", fmt::ptr(this))};

    ZjChronoCount overtime_count_ {0};
    ZjChronoCount overtime_count_limit_ {0};

    ZjChronoNs period_ {0};
    ZjChronoTimePoint start_time_ {ZjChronoClock::now()};
    ZjChronoNs time_spent_ {0};
    ZjChronoNs time_left_ {0};

    ZjChronoCount total_count_ {0};
    ZjChronoCount total_time_spent {0};
};
