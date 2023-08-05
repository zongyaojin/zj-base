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

/// @brief ZjLog singleton class; @warning This class should NOT use any of the debugging or logging macros, since they rely on ZjLogAgents,
/// which relies on this class to actually log information, using those macros in this class would cause "circular reference"
class ZjLog : public ZjSingleton<ZjLog>
{
public:
    using CoreLogLevel = spdlog::level::level_enum;
    using CoreLogPtr = std::shared_ptr<spdlog::logger>;

public:
    /**
     * @brief Log a message with specified log level
     *
     * @param level Log level
     * @param msg Log message
     */
    void log(const ZjLogLevel level, std::string&& msg);

    /// @warning This initializes the spdlog thread, which means this should be initialized before any logging
    void init();

    /// @warning This shuts down the entire spdlog, which means this should be called only when the whole program terminates
    void shutdown();

    inline const std::string& fileName() const { return m_fileName; }

private:
    /// Log implementation's pointer
    CoreLogPtr m_logger;

    /// Log file name
    std::string m_fileName;

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