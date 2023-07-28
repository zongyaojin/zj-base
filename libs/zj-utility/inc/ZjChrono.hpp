#pragma once

#include <chrono>
#include "ZjConcepts.hpp"

class ZjChrono final
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
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Count = TimePoint::rep;

    using Ns = std::chrono::nanoseconds;
    using Us = std::chrono::microseconds;
    using Ms = std::chrono::milliseconds;
    using Sec = std::chrono::seconds;

public:
    static constexpr double s_nsToSec {1.0e-9};
    static constexpr double s_nsToMs {1.0e-6};
    static constexpr double s_nsToUs {1.0e-3};

    static constexpr double s_usToSec {1.0e-6};
    static constexpr double s_usToMs {1.0e-3};
    static constexpr double s_usToNs {1.0e+3};

    static constexpr double s_msToSec {1.0e-3};
    static constexpr double s_msToUs {1.0e+3};
    static constexpr double s_msToNs {1.0e+6};

    static constexpr double s_secToMs {1.0e+3};
    static constexpr double s_secToUs {1.0e+6};
    static constexpr double s_secToNs {1.0e+9};

public:
    template <ZjDuration T>
    inline static auto getTimeCount()
    {
        return std::chrono::time_point_cast<T>(Clock::now()).time_since_epoch().count();
    }

    static auto getTime(const Unit unit);
};