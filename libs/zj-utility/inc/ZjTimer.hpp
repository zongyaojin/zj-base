#pragma once

#include "fmt/format.h"

#include "ZjDebug.hpp"
#include "ZjChrono.hpp"

class ZjTimer
{
public:
    enum class Unit : std::int8_t
    {
        Sec = 0,
        Ms,
        Us,
        Ns,
    };

public:
    ZjTimer(const std::string name = "");
    ~ZjTimer() = default;

    void init(const unsigned frequency, const unsigned overtimeCountLimit = 0);

    inline void start() { m_startTime = ZjChrono::Clock::now(); }
    
    bool guard();

    inline ZjChrono::Count getTotalCount() const { return m_totalCount; };

    double getLoopAvg(const Unit unit) const;

private:
    std::string m_name {fmt::format("ZjTimer-{}", fmt::ptr(this))};

    ZjChrono::Count m_totalCount {0};
    ZjChrono::Count m_totalTimeSpent {0};

    ZjChrono::Count m_overtimeCount {0};
    ZjChrono::Count m_overtimeCountLimit {0};
    ZjChrono::Count m_totalOvertimeCount {0};

    ZjChrono::Ns m_period;
    ZjChrono::TimePoint m_startTime;
    ZjChrono::Ns m_timeSpent;
    ZjChrono::Ns m_timeLeft;
};