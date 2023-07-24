#include "ZjChrono.hpp"

namespace {
using namespace std::chrono;
}

auto ZjChrono::getNsCount()
{
    return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count();
}

auto ZjChrono::getUsCount()
{
    return time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch().count();
}

auto ZjChrono::getMsCount()
{
    return time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
}

auto ZjChrono::getSecCount()
{
    return time_point_cast<seconds>(high_resolution_clock::now()).time_since_epoch().count();
}

double ZjChrono::getNs()
{
    return static_cast<double>(ZjChrono::getNsCount());
}

double ZjChrono::getUs()
{
    return static_cast<double>(ZjChrono::getNsCount()) * 1.0e-3;
}

double ZjChrono::getMs()
{
    return static_cast<double>(ZjChrono::getNsCount()) * 1.0e-6;
}

double ZjChrono::getSec()
{
    return static_cast<double>(ZjChrono::getNsCount()) * 1.0e-9;
}
