#pragma once

#include <chrono>

class ZjChrono final
{
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

public:
    static auto getNsCount();
    static auto getUsCount();
    static auto getMsCount();
    static auto getSecCount();

    static double getNs();
    static double getUs();
    static double getMs();
    static double getSec();
};