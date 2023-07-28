#include "ZjLog.hpp"
#include <chrono>

#include "fmt/format.h"
#include "fmt/chrono.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

namespace {

constexpr size_t k_maxFileSize = 1024 * 1024 * 10;
constexpr size_t k_maxNumFiles = 3;

constexpr size_t k_qSize = 8192;
constexpr size_t k_threadCount = 1;

}

void ZjLog::log(const ZjLogLevel level, std::string&& msg)
{
    if (!m_logger) {
        // https://stackoverflow.com/a/74987040
        auto now = std::chrono::system_clock::now();
        auto sse = now.time_since_epoch();
        auto time = fmt::format("{:%F_%H:%M:}{:%S}", now, sse);

        m_logFileName = fmt::format("{}/zj-logs/{}_{}.txt", __ZJ_PKG_BUILD_PATH__, __ZJ_PKG_NAME__, time);

        // https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
        spdlog::init_thread_pool(k_qSize, k_threadCount);
        auto stdoutSink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        auto rotatingFileSink {std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_logFileName, k_maxFileSize, k_maxNumFiles)};

        m_sinks.push_back(stdoutSink);
        m_sinks.push_back(rotatingFileSink);

        m_logger = std::make_shared<spdlog::async_logger>(
            __ZJ_PKG_NAME__, m_sinks.begin(), m_sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(m_logger);

        m_logger->flush_on(spdlog::level::info);
        m_logger->set_level(spdlog::level::trace);

        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
        m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");
    }

    m_logger->log(mk_logLevelMap.at(level), msg);
}

void ZjLog::shutdown()
{
    if (m_logger) {
        m_logger->flush();
    }

    m_logger.reset();
    m_sinks.clear();
    spdlog::shutdown();
}
