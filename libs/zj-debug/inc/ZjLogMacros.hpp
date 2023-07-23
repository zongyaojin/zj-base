#pragma once

#include "ZjLogAgents.hpp"
#include "ZjBasicMacros.hpp"

#include <cstdint>
#include <type_traits>
#include <chrono>

#define _ZJ_ASSERT(condition, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if (!(condition)) {                                                                                                                \
            _ZjAssert(#condition, std::source_location::current(), ##__VA_ARGS__);                                                         \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_MSG(level, msg, ...)                                                                                                           \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(level), ZjL>, ZJ_B_YELLOW "level has to be a ZjL" ZJ_PLAIN);                                 \
        static_assert(level != ZjL::Error && level != ZjL::Critical, ZJ_B_YELLOW "Error & Critical reserved for _ZjThrow()" ZJ_PLAIN);     \
        _ZjMessage(level, std::source_location::current(), msg, ##__VA_ARGS__);                                                            \
    } while (0)

#define _ZJ_MSG_T(level, intervalS, msg, ...)                                                                                              \
    do {                                                                                                                                   \
        static_assert(std::is_convertible_v<decltype(intervalS), double>, ZJ_B_YELLOW "intervalS doesn't evaluate to double" ZJ_PLAIN);    \
        static_assert(intervalS > 0.1, ZJ_B_YELLOW "intervalS should be greater than 0.1" ZJ_PLAIN);                                       \
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
        constexpr std::uint64_t intervalNs = intervalS * 1e9;                                                                              \
        if (elapsed > DurationNs {intervalNs}) {                                                                                           \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
            lastTime = now;                                                                                                                \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_MSG_IF(condition, level, msg, ...)                                                                                             \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_MSG_T_IF(condition, level, intervalS, msg, ...)                                                                                \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_MSG_T(level, intervalS, msg, ##__VA_ARGS__);                                                                               \
        }                                                                                                                                  \
    } while (0)
