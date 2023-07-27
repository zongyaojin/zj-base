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
static constexpr const char* k_assertFmt {"{}:{}:{} @ `{}` | [{}]\n{}\n"};
static constexpr const char* k_traceFmt {"{}:{}:{} @ `{}`; {}"};
}
}
}

template <typename... Args>
void _ZjAssert(const char* condition, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string userMsg {fmt::format(fmt::runtime(fmt), args...)};
    ZjLog::getInstance().log(ZjL::Critical,
        fmt::format(zj::log::agents::k_assertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(userMsg)));
    ZjLog::getInstance().shutdown();
    std::abort();
}

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
