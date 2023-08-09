/**
 * @file ZjLogAgents.hpp
 *
 * @brief Logging agents to be used in the log macros, the agents deal with the ZjLog class
 * @note Client code should use the macros, the log macros use the agents, and the agents interact with the ZjLog
 *
 * @author Zongyao Jin
 * @date 2023-07-26
 */

#pragma once

#include "ZjLog.hpp"
#include "ZjColors.hpp"

#include <source_location>
#include <string>
#include <cstdint>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace zj {
namespace log {
namespace agents {

/// Assertion message formatter
static constexpr const char* k_assertFmt {"{}:{}:{} @ `{}` | [{}]\n{}\n"};

/// Trace message formatter
static constexpr const char* k_traceFmt {"{}:{}:{} @ `{}`; {}"};

}
}
}

/**
 * @brief Assertion with source location, user messages, and log support
 *
 * @tparam Args Variadic template arguments for fmt formatted messages
 * @param condition Condition from macro converted to const char pointer
 * @param s Source location
 * @param fmt Formatter string
 * @param args Variadic template arguments
 *
 * @warning Client code should use macro _ZJ_ASSERT, not this function, to get condition evaluated and source location taken care of
 */
template <typename... Args>
void _ZjAssert(const char* condition, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string userMsg {fmt::format(fmt::runtime(fmt), args...)};
    ZjLog::getInstance().log(ZjL::Critical,
        fmt::format(zj::log::agents::k_assertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(userMsg)));
    ZjLog::getInstance().shutdown();
    std::abort();
}

/**
 * @brief Message function with source location, user message, and log support
 *
 * @tparam Args Args Variadic template arguments for fmt formatted messages
 * @param level Logging level
 * @param s Source location
 * @param fmt Formatter string
 * @param args Variadic template arguments
 *
 * @warning Client code should use macros in ZjLogMacroExtensions.hpp, not this function, to get source location taken care of
 */
template <typename... Args>
void _ZjMessage(const ZjLogLevel level, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    switch (level) {
        case ZjLogLevel::Trace: {
            std::string userMsg {fmt::format(fmt::runtime(fmt), args...)};
            ZjLog::getInstance().log(ZjL::Trace,
                fmt::format(zj::log::agents::k_traceFmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(userMsg)));
        } break;
        case ZjLogLevel::Debug: {
            ZjLog::getInstance().log(ZjL::Debug, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Info: {
            ZjLog::getInstance().log(ZjL::Info, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Warn: {
            ZjLog::getInstance().log(ZjL::Warn, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Error: {
            ZjLog::getInstance().log(ZjL::Error, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Critical: {
            ZjLog::getInstance().log(ZjL::Critical, fmt::format(fmt::runtime(fmt), args...));
        } break;
        default:
            ZjLog::getInstance().log(ZjL::Critical, fmt::format("unsupported log level, [{}]", static_cast<std::uint8_t>(level)));
            std::abort();
    }
}
