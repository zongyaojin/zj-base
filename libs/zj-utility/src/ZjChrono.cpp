#include "ZjChrono.hpp"

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
