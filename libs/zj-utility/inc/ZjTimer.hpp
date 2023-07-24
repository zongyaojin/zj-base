#pragma once

#include "fmt/format.h"

#include "ZjDebug.hpp"
#include "ZjChrono.hpp"

class ZjTimer
{
public:
    ZjTimer(const std::string name = "");
    ~ZjTimer() = default;

    void init(const unsigned frequency, const unsigned overtimeCountLimit = 0);

    void start();

    void guard();

    double getAvgInSec() const;
    double getAvgInMs() const;
    double getAvgInUs() const;
    double getAvgInNs() const;

private:
    std::string m_name {fmt::format("timer-{}", fmt::ptr(this))};

    ZjChrono::Count m_totalCount {0};
    ZjChrono::Count m_totalTimeSpent {0};

    ZjChrono::Count m_overtimeCount {0};
    ZjChrono::Count m_overtimeCountLimit {0};

    ZjChrono::Ns m_period;
    ZjChrono::TimePoint m_startTime;
    ZjChrono::Ns m_timeSpent;
    ZjChrono::Ns m_timeLeft;
};