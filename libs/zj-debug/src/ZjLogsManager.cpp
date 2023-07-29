#include "ZjLogsManager.hpp"
#include "spdlog/spdlog-inl.h"
#include "spdlog/async.h"

void ZjLogsManager::init(const size_t qSize, const size_t threadCount)
{
    if (m_initialized) {
        return;
    }

    // https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
    spdlog::init_thread_pool(qSize, threadCount);
}

void ZjLogsManager::registerLogger(CoreLogPtr loggerPtr)
{
    spdlog::register_logger(loggerPtr);
}

void ZjLogsManager::dropLogger(const std::string& loggerName)
{
    spdlog::drop(loggerName);
}

void ZjLogsManager::shutdown()
{
    spdlog::shutdown();
    m_initialized = false;
}
