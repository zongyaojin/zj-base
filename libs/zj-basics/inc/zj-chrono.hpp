/**
 * @file zj-chrono.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-concepts.hpp"

#include <chrono>
#include <string>

namespace zj {

constexpr double kNsToSec {1.0e-9};
constexpr double kNsToMs {1.0e-6};
constexpr double kNsToUs {1.0e-3};

constexpr double kUsToSec {1.0e-6};
constexpr double kUsToMs {1.0e-3};
constexpr double kUsToNs {1.0e+3};

constexpr double kMsToSec {1.0e-3};
constexpr double kMsToUs {1.0e+3};
constexpr double kMsToNs {1.0e+6};

constexpr double kSecToMs {1.0e+3};
constexpr double kSecToUs {1.0e+6};
constexpr double kSecToNs {1.0e+9};

} // namespace zj

using ZjChronoNs = std::chrono::nanoseconds;
using ZjChronoUs = std::chrono::microseconds;
using ZjChronoMs = std::chrono::milliseconds;
using ZjChronoSec = std::chrono::seconds;

using ZjChronoClock = std::chrono::high_resolution_clock;
using ZjChronoTimePoint = ZjChronoClock::time_point;
using ZjChronoCount = ZjChronoTimePoint::rep;

enum class ZjChronoUnit : std::int8_t
{
    kSec = 0,
    kMs,
    kUs,
    kNs,
};

/// Get epoch time by count based on duration type
template <ZjDuration T>
inline ZjChronoCount ZjGetTimeEpochCount()
{
    return std::chrono::time_point_cast<T>(ZjChronoClock::now()).time_since_epoch().count();
}

/// Get epoch time by double in second
double ZjGetTimeEpoch(const ZjChronoUnit unit);

/// Get ISO time by string
std::string ZjGetTimeIso();
