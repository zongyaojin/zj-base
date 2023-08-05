#include "ZjChrono.hpp"
#include "fmt/chrono.h"

auto ZjChrono::getTime(const Unit unit)
{
    double conversion {0.0};
    switch (unit) {
        case Unit::Ns:
            conversion = 1.0;
            break;
        case Unit::Us:
            conversion = s_nsToUs;
            break;
        case Unit::Ms:
            conversion = s_nsToMs;
            break;
        case Unit::Sec:
            conversion = s_nsToSec;
            break;
        default:
            conversion = 0.0;
    }

    return ZjChrono::getTimeCount<Ns>() * conversion;
}

std::string ZjChrono::getTimeIso()
{
    // https://stackoverflow.com/a/74987040
    auto now = std::chrono::system_clock::now();
    auto sse = now.time_since_epoch();
    auto time = fmt::format("{:%F_%H:%M:}{:%S}", now, sse);

    return time;
}
