#pragma once

#include "ZjLogAgents.hpp"
#include "ZjUtilityMacros.hpp"

#define _ZJ_ASSERT(condition, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if (!(condition)) {                                                                                                                \
            _ZjAssert(#condition, std::source_location::current(), ##__VA_ARGS__);                                                         \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_MSG(level, msg, ...)                                                                                                           \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(level), ZjL>, ZJ_B_YELLOW "first argument of `_ZJ_MSG()` has to be an ZjL" ZJ_PLAIN);        \
        static_assert(level != ZjL::Error && level != ZjL::Critical,                                                                       \
            ZJ_B_YELLOW "ZjL::Error & ZjL::Critical are reserved for internal use" ZJ_PLAIN);                                              \
        _ZjMessage(level, std::source_location::current(), msg, ##__VA_ARGS__);                                                            \
    } while (0)

#define _ZJ_MSG_IF(condition, level, msg, ...)                                                                                             \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_MSG(level, msg, ##__VA_ARGS__);                                                                                            \
        }                                                                                                                                  \
    } while (0)
