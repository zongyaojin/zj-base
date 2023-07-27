/**
 * @file ZjLog.hpp
 *
 * @brief ZjLog level types enum and singleton logger
 *
 * @author Zongyao Jin
 * @date 2023-07-26
 */

#pragma once

#include "ZjSingleton.hpp"
#include <unordered_map>

#include "spdlog/spdlog.h"

/// Zj log level type enum
enum class ZjLogLevel : std::uint8_t
{
    Trace = 0,
    Debug,
    Info,
    Warn,
    Error,
    Critical,
    Off,
};

/// Zj log level short alias
using ZjL = ZjLogLevel;

/// ZjLog singleton class
class ZjLog : public ZjSingleton<ZjLog>
{
    /// Alias for the underlying log implementation's log level
    using CoreLogLevel = spdlog::level::level_enum;

    /// Alias for the underlying log implementation's log pointer
    using CoreLogPtr = std::shared_ptr<spdlog::logger>;

public:
    /**
     * @brief Log a message with specified log level
     *
     * @param level Log level
     * @param msg Log message
     */
    void log(const ZjLogLevel level, std::string&& msg);

    /// Shutdown the logger
    void shutdown();

private:
    /// Log implementation's pointer
    CoreLogPtr m_logger;

    /// Log sinks
    std::vector<spdlog::sink_ptr> m_sinks;

    /// Zj log level to implementation's log level map
    const std::unordered_map<ZjLogLevel, CoreLogLevel> mk_logLevelMap {
        {ZjL::Trace, CoreLogLevel::trace},
        {ZjL::Debug, CoreLogLevel::debug},
        {ZjL::Info, CoreLogLevel::info},
        {ZjL::Warn, CoreLogLevel::warn},
        {ZjL::Error, CoreLogLevel::err},
        {ZjL::Critical, CoreLogLevel::critical},
        {ZjL::Off, CoreLogLevel::off},
    };
};