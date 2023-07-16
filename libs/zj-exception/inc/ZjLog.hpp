#pragma once

#include "ZjSingleton.hpp"

#include <unordered_map>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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

using ZjL = ZjLogLevel;

class ZjLog : public ZjSingleton<ZjLog>
{
    using CoreLogLevel = spdlog::level::level_enum;
    using CoreLogPtr = std::shared_ptr<spdlog::logger>;

public:
    void log(const ZjLogLevel level, std::string&& msg);

private:
    CoreLogPtr m_logger;

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