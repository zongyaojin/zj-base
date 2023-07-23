#pragma once

#include <chrono>

class ZjTimeNow final
{
public:
    static auto getNanosecCount();
    static auto getMicrosecCount();
    static auto getMillisecCount();
    static auto getSecCount();

    static double getNanosec();
    static double getMicrosec();
    static double getMillisec();
    static double getSec();
};