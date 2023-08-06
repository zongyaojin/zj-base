#include "ZjLog.hpp"
#include "ZjColors.hpp"
#include "ZjChrono.hpp"

#include "fmt/format.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

namespace {

static constexpr size_t k_defaultQSize = 8192;
static constexpr size_t k_defaultThreadCount = 1;

static constexpr size_t k_maxFileSize {1024 * 1024 * 10};
static constexpr size_t k_maxNumFiles {3};

static constexpr const char* k_logFolderName {"zj-logs"};

}

void ZjLog::log(const ZjLogLevel level, std::string&& msg)
{
    if (m_logger) {
        m_logger->log(mk_logLevelMap.at(level), msg);
        return;
    }

    init();
    m_logger->log(mk_logLevelMap.at(level), msg);
}

void ZjLog::init(const std::string& userFolderNoSlash)
{
    if (m_logger) {
        return;
    }

    m_userFolderNoSlash = userFolderNoSlash;

    std::string logSaveFolder = m_userFolderNoSlash.empty() ? fmt::format("{}/{}", __ZJ_PKG_BUILD_PATH_NO_SLASH__, k_logFolderName)
                                                            : fmt::format("{}/{}", m_userFolderNoSlash, k_logFolderName);

    m_fileName = fmt::format("{}/{}_{}.txt", logSaveFolder, __ZJ_PKG_NAME__, ZjChrono::getTimeIso());

    /// @see https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
    /// @note Using default thread settings, and one thread should be enough for both ZjLog and a few csv logs
    spdlog::init_thread_pool(k_defaultQSize, k_defaultThreadCount);

    auto stdoutSink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    auto rotatingFileSink {std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_fileName, k_maxFileSize, k_maxNumFiles)};
    std::vector<spdlog::sink_ptr> sinks {stdoutSink, rotatingFileSink};

    m_logger = std::make_shared<spdlog::async_logger>(
        __ZJ_PKG_NAME__, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

    m_logger->flush_on(spdlog::level::info);
    m_logger->set_level(spdlog::level::trace);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");
}

void ZjLog::shutdown()
{
    if (m_logger) {
        m_logger->log(CoreLogLevel::info, "ZjLog shuting down in 3...");
        m_logger->log(CoreLogLevel::info, "ZjLog shuting down in 2...");
        m_logger->log(CoreLogLevel::info, "ZjLog shuting down in 1...");

        // since logger is set to flush only on info level, this forces a flush before shutdown to make sure all messages get logged
        m_logger->flush();
    }

    m_logger.reset();
    spdlog::shutdown();
}
