#include "ZjTimeNow.hpp"

namespace {
using namespace std::chrono;
}

auto ZjTimeNow::getNanosecCount()
{
    return time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count();
}

auto ZjTimeNow::getMicrosecCount()
{
    return time_point_cast<microseconds>(system_clock::now()).time_since_epoch().count();
}

auto ZjTimeNow::getMillisecCount()
{
    return time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
}

auto ZjTimeNow::getSecCount()
{
    return time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();
}

double ZjTimeNow::getNanosec()
{
    return static_cast<double>(ZjTimeNow::getNanosecCount());
}

double ZjTimeNow::getMicrosec()
{
    return static_cast<double>(ZjTimeNow::getNanosecCount()) * 1.0e-3;
}

double ZjTimeNow::getMillisec()
{
    return static_cast<double>(ZjTimeNow::getNanosecCount()) * 1.0e-6;
}

double ZjTimeNow::getSec()
{
    return static_cast<double>(ZjTimeNow::getNanosecCount()) * 1.0e-9;
}
