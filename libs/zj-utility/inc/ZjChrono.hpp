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
    static auto getNsCount();
    static auto getUsCount();
    static auto getMsCount();
    static auto getSecCount();

    static double getNs();
    static double getUs();
    static double getMs();
    static double getSec();
};