/**
 * @file zj-logging-agents.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @brief Logging agents to be used in the log macros, the agents deal with the ZjLogger class
 * @warning Client code should use the macros, not functions here; the log macros use the agents, and the agents interact with the ZjLogger
 */

#pragma once

#include "zj-logger.hpp"
#include "zj-colors.hpp"
#include "zj-formatters.hpp"

#include <source_location>
#include <string>
#include <memory>
#include <utility>

#include <cstdint>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

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
    ZjLogger::GetInstance().Log(ZjL::kCritical,
        fmt::format(zj::kAssertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(user_msg)));
    ZjLogger::GetInstance().Shutdown();
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
 * @warning Client code should use macros in zj-logging-macros-simplified.hpp, not this function, to get source location taken care of
 */
template <typename... Args>
void _ZjMessage(const ZjLogLevel level, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    switch (level) {
        case ZjLogLevel::kTrace: {
            std::string user_msg {fmt::format(fmt::runtime(fmt), args...)};
            ZjLogger::GetInstance().Log(ZjL::kTrace,
                fmt::format(zj::kTraceFmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(user_msg)));
        } break;
        case ZjLogLevel::kDebug: {
            ZjLogger::GetInstance().Log(ZjL::kDebug, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::kInfo: {
            ZjLogger::GetInstance().Log(ZjL::kInfo, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::kWarn: {
            ZjLogger::GetInstance().Log(ZjL::kWarn, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::kError: {
            ZjLogger::GetInstance().Log(ZjL::kError, fmt::format(fmt::runtime(fmt), args...));
        } break;
        case ZjLogLevel::kCritical: {
            ZjLogger::GetInstance().Log(ZjL::kCritical, fmt::format(fmt::runtime(fmt), args...));
        } break;
        default:
            ZjLogger::GetInstance().Log(ZjL::kCritical, fmt::format("unsupported log level, [{}]", static_cast<std::uint8_t>(level)));
            std::abort();
    }
}
