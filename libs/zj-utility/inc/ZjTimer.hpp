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

    inline void start() { m_startTime = ZjChrono::Clock::now(); }
    void guard();

    inline const std::string& name() const { return m_name; }
    inline ZjChrono::Count totalCount() const { return m_totalCount; };

    double loopAvg(const ZjChrono::Unit unit) const;
    double period(const ZjChrono::Unit unit) const;
    inline ZjChrono::Count overtimeCount() const { return m_overtimeCount; }

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