/**
 * @file ZjLogAgents.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @brief Logging agents to be used in the log macros, the agents deal with the ZjLog class
 * @warning Client code should use the macros, not functions here; the log macros use the agents, and the agents interact with the ZjLog
 */

#pragma once

#include "ZjLog.hpp"
#include "zj-colors.hpp"

#include <source_location>
#include <string>
#include <memory>
#include <utility>

#include <cstdint>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace zj {
namespace log {
namespace agents {

/// Assertion message formatter
static constexpr const char* k_assertFmt {"{}:{}:{} @ `{}` | [{}]\n  {}\n"};

/// Trace message formatter
static constexpr const char* k_traceFmt {"{}:{}:{} @ `{}` | {}"};

} // namespace agents
} // namespace log
} // namespace zj

/**
 * @brief Assertion with source location, user messages, and log support
 *
 * @tparam Args Variadic template arguments for fmt formatted messages
 * @param[in] condition Condition literal from macro converted to const char pointer
 * @param[in] s Source location
 * @param[in] fmt Formatter string
 * @param[in] args Variadic template arguments
 *
 * @warning Client code should use macro _ZJ_ASSERT, not this function, to get condition evaluated and source location taken care of
 */
template <typename... Args>
void _ZjAssert(const char* condition, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string user_msg {fmt::format(fmt::runtime(fmt), args...)};
    ZjLog::GetInstance().log(ZjL::Critical,
        fmt::format(zj::log::agents::k_assertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(user_msg)));
    ZjLog::GetInstance().shutdown();
    std::abort();
}

/**
 * @brief Message function with source location, user message, and log support
 *
 * @tparam Args Args Variadic template arguments for fmt formatted messages
 * @param[in] level Logging level
 * @param[in] s Source location
 * @param[in] fmt Formatter string
 * @param[in] args Variadic template arguments
 *
 * @warning Client code should use macros in ZjLogMacroExtensions.hpp, not this function, to get source location taken care of
 */
template <typename... Args>
void _ZjMessage(const ZjLogLevel level, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    switch (level) {
        case ZjLogLevel::Trace: {
            std::string user_msg {fmt::format(fmt::runtime(fmt), args...)};
            ZjLog::GetInstance().log(ZjL::Trace,
                fmt::format(zj::log::agents::k_traceFmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(user_msg)));
        } break;
        case ZjLogLevel::Debug: {
            ZjLog::GetInstance().log(ZjL::Debug, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Info: {
            ZjLog::GetInstance().log(ZjL::Info, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Warn: {
            ZjLog::GetInstance().log(ZjL::Warn, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Error: {
            ZjLog::GetInstance().log(ZjL::Error, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::Critical: {
            ZjLog::GetInstance().log(ZjL::Critical, fmt::format(fmt::runtime(fmt), args...));
        } break;
        default:
            ZjLog::GetInstance().log(ZjL::Critical, fmt::format("unsupported log level, [{}]", static_cast<std::uint8_t>(level)));
            std::abort();
    }
}
