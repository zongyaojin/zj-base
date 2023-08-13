/**
 * @file ZjLogMacros.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @warning Client code is recommended to use macros in ZjLogMacroExtensions, not in this file
 */

#pragma once

#include "ZjLogAgents.hpp"
#include "ZjBasicMacros.hpp"

#include <cstdint>
#include <type_traits>
#include <chrono>

/// Message interface
#define _ZJ_MSG(level, msg, ...)                                                                                                           \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(level), ZjL>, "level has to be a ZjL");                                                      \
        static_assert(level != ZjL::Error && level != ZjL::Critical, "Error & Critical reserved for _ZjThrow()");                          \
        _ZjMessage(level, std::source_location::current(), msg, ##__VA_ARGS__);                                                            \
    } while (0)

/// @brief Message interface, but this one only logs/prints if the condition is true
#define _ZJ_MSG_IF(condition, level, msg, ...)                                                                                             \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
        }                                                                                                                                  \
    } while (0)

/// @brief Periodic message interface that will print/log the message when it's first called, then every intervalSec second(s)
/// @note The macro replacement creates a do-while clause at each call site, and the brackets create a local scope; which means that the
/// static variables are defined in these local scopes, so they are unique to each call site, which can help keep track of local "scoped"
/// time elapse, which is wonderful
#define _ZJ_MSG_T(level, intervalSec, msg, ...)                                                                                            \
    do {                                                                                                                                   \
        static_assert(std::is_convertible_v<decltype(intervalSec), double>, "intervalSec doesn't evaluate to double");                     \
        static_assert(intervalSec >= 0.1, "intervalSec should be at least 0.1");                                                           \
                                                                                                                                           \
        using Clock = std::chrono::high_resolution_clock;                                                                                  \
        using TimePoint = Clock::time_point;                                                                                               \
        using DurationNs = std::chrono::nanoseconds;                                                                                       \
                                                                                                                                           \
        static bool firstTime = true;                                                                                                      \
        static TimePoint lastTime = Clock::now();                                                                                          \
        TimePoint now = Clock::now();                                                                                                      \
        DurationNs elapsed = std::chrono::duration_cast<DurationNs>(now - lastTime);                                                       \
                                                                                                                                           \
        if (firstTime) {                                                                                                                   \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
            firstTime = false;                                                                                                             \
        }                                                                                                                                  \
                                                                                                                                           \
        constexpr std::uint64_t intervalNs = intervalSec * 1e9;                                                                            \
        if (elapsed > DurationNs {intervalNs}) {                                                                                           \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
            lastTime = now;                                                                                                                \
        }                                                                                                                                  \
    } while (0)

/// Periodic message interface like _ZJ_MSG_T, but this one only logs/prints if the condition is true
#define _ZJ_MSG_T_IF(condition, level, intervalSec, msg, ...)                                                                              \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_MSG_T(level, intervalSec, msg, ##__VA_ARGS__);                                                                             \
        }                                                                                                                                  \
    } while (0)
