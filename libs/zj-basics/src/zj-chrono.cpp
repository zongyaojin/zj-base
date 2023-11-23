/**
 * @file zj-chrono.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "zj-chrono.hpp"
#include "fmt/chrono.h"

double ZjGetTimeEpoch(const ZjChronoUnit unit)
{
    double conversion {1.0};
    switch (unit) {
        case ZjChronoUnit::kNs:
            break;
        case ZjChronoUnit::kUs:
            conversion = zj::kNsToUs;
            break;
        case ZjChronoUnit::kMs:
            conversion = zj::kNsToMs;
            break;
        case ZjChronoUnit::kSec:
            conversion = zj::kNsToSec;
            break;
        default:
            conversion = 0.0;
    }

    return ZjGetTimeEpochCount<ZjChronoNs>() * conversion;
}

std::string ZjGetTimeIso()
{
    // https://stackoverflow.com/a/74987040
    auto now = std::chrono::system_clock::now();
    auto sse = now.time_since_epoch();
    auto time = fmt::format("{:%F_%H:%M:}{:%S}", now, sse);

    return time;
}
