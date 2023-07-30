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
    m_initialized = true;
}

void ZjLogsManager::registerLogger(CoreLogPtr loggerPtr, PreDropRoutine preDropRoutine)
{
    if (!m_initialized) {
        init();
    }

    spdlog::register_logger(loggerPtr);
    m_loggerPreDrops.emplace(loggerPtr->name(), preDropRoutine);
}

void ZjLogsManager::dropLogger(const LoggerName& loggerName)
{
    if (!m_initialized) {
        return;
    }

    auto it {m_loggerPreDrops.find(loggerName)};

    if (it != m_loggerPreDrops.end()) {
        if (it->second) {
            it->second();
        }
        spdlog::drop(loggerName);
        m_loggerPreDrops.erase(it);
    }
}

void ZjLogsManager::shutdown()
{
    if (!m_initialized) {
        return;
    }

    for (const auto& pair : m_loggerPreDrops) {
        pair.second();
    }

    m_loggerPreDrops.clear();
    spdlog::shutdown();
    m_initialized = false;
}
