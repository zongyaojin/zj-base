#pragma once

#include "ZjSingleton.hpp"
#include "spdlog/spdlog.h"
#include <unordered_map>
#include <functional>

/**
 * @brief A class that manages all log classes; Since all log classes share the same thread(s) from the underlying library, the
 * responsibility are all put in this one single place to make it easier to work with.
 * @note The init and shutdown of this class can be placed in ZjProgramSwitch, but that would introduce a strong coupling, which seems to
 * outweigh the benefits, so let's not do that.
 */
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

    using LoggerName = std::string;
    using PreDropRoutine = std::function<void()>;

public:
    /// Init q size, num of threads, 1 thread should be enough for a few loggers
    void init(const size_t qSize = s_defaultQSize, const size_t threadCount = s_defaultThreadCount);

    /// @brief Register a logger with its pre-drop routine, which could contain flushing data, sinks memory clean up, etc.
    /// @note If ZjLogsManager isn't initialized, it will be first default-initialized in this function first
    void registerLogger(CoreLogPtr loggerPtr, PreDropRoutine preDropRoutine = nullptr);

    /// Drop a logger if ZjLogsManager is initialized and there exists such a logger
    void dropLogger(const LoggerName& loggerName);

    /// @brief Shutdown all loggers; @note ZjProgramSwitch::turnOff will call this function
    void shutdown();

private:
    /// Initialization flag
    bool m_initialized {false};

    /// Loggers pre-drop routine for data flushing, memory clean up, etc., if any
    std::unordered_map<LoggerName, PreDropRoutine> m_loggerPreDrops;
};
