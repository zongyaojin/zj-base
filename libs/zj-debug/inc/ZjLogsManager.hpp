#pragma once

#include "ZjSingleton.hpp"
#include "spdlog/spdlog.h"

class ZjLogsManager : public ZjSingleton<ZjLogsManager>
{
public:
    /// @{ https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
    static constexpr size_t s_defaultQSize = 8192;
    static constexpr size_t s_defaultThreadCount = 1;
    /// @}

    // Alias for the underlying log implementation's log level
    using CoreLogLevel = spdlog::level::level_enum;

    /// Alias for the underlying log implementation's log pointer
    using CoreLogPtr = std::shared_ptr<spdlog::logger>;

public:
    /// Init q size, num of threads
    void init(const size_t qSize = s_defaultQSize, const size_t threadCount = s_defaultThreadCount);

    /// Shutdown
    void shutdown();

    /// Register logger
    void registerLogger(CoreLogPtr loggerPtr);

    /// Drop logger
    void dropLogger(const std::string& loggerName);

private:
    bool m_initialized {false};
};
