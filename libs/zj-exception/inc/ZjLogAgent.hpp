#pragma once

#include <source_location>
#include <string>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace zj {
namespace log {
namespace agent {
static constexpr const char* k_assertFmt {"{}:{}:{} @ `{}` | " ZJ_B_CYAN "[{}]" ZJ_PLAIN "\n{}\n" ZJ_PLAIN};
}
}
}

/**
 * @brief
 *
 * @tparam Args
 * @param condition
 * @param s
 * @param fmt
 * @param args
 */
template <typename... Args>
void _ZjAssert(const char* condition, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string userMsg {fmt::format(fmt::runtime(fmt), args...)};
    spdlog::critical(zj::log::agent::k_assertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(userMsg));
    std::abort();
}

/**
 * @brief
 *
 */
#define _ZJ_STATIC_CHECK_BOOLEAN(condition)                                                                                                \
    do {                                                                                                                                   \
        using conditionType = std::remove_cv_t<decltype(condition)>;                                                                       \
        constexpr bool boolType {std::is_same_v<conditionType, bool>};                                                                     \
        static_assert(boolType, ZJ_B_YELLOW "condition does not evaluate to boolean" ZJ_PLAIN);                                            \
    } while (0)

/**
 * @brief
 *
 */
#define _ZJ_ASSERT(condition, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_CHECK_BOOLEAN(condition);                                                                                               \
        if (!(condition)) {                                                                                                                \
            _ZjAssert(#condition, std::source_location::current(), ##__VA_ARGS__);                                                         \
        }                                                                                                                                  \
    } while (0)
