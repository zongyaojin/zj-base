#include "ZjLog.hpp"
#include "ZjColors.hpp"
#include "ZjChrono.hpp"
#include "ZjBasicMacros.hpp"

#include <cstdio>

#include "fmt/format.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

namespace {

// https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
static constexpr size_t k_defaultLogThreadQSize = 8192;
static constexpr size_t k_defaultLogThreadCount = 1;

static constexpr size_t k_maxLogFileSize {1024 * 1024 * 10};
static constexpr size_t k_maxLogNumFiles {3};

static constexpr const char* k_logSubFolderName {"zj-logs"};

}  // namespace

void ZjLog::log(const ZjLogLevel level, std::string&& msg)
{
    if (m_logger) {
        m_logger->log(mk_logLevelMap.at(level), msg);
        return;
    }

    init();
    m_logger->log(mk_logLevelMap.at(level), msg);
}

void ZjLog::init(const std::string& csvLogFolderNoSlash, const std::string& regularLogFolderNoSlash)
{
    if (m_logger) {
        return;
    }

    m_csvLogFolderNoSlash = csvLogFolderNoSlash;
    m_regularLogFolderNoSlash = regularLogFolderNoSlash;

    {
        auto regularFolderInfo
            = m_regularLogFolderNoSlash.empty()
                  ? fmt::format(ZJ_B_GREEN "ZjLog not saving regular log to file" ZJ_PLAIN)
                  : fmt::format(ZJ_B_GREEN "ZjLog sets regular log base folder to [{}]" ZJ_PLAIN, m_regularLogFolderNoSlash);
        auto csvFolderInfo = m_csvLogFolderNoSlash.empty()
                                 ? fmt::format(ZJ_B_GREEN "ZjLog using default csv log base folder" ZJ_PLAIN)
                                 : fmt::format(ZJ_B_GREEN "ZjLog sets csv log base folder to [{}]" ZJ_PLAIN, m_csvLogFolderNoSlash);

        // Logger not initialized, using raw console print
        printf("\n\t%s\n", regularFolderInfo.c_str());
        printf("\t%s\n\n", csvFolderInfo.c_str());
    }

    // If regular log folder folder is empty, do not create log file, only log to console
    if (!m_regularLogFolderNoSlash.empty()) {
        std::string logSaveFolder {fmt::format("{}/{}", m_regularLogFolderNoSlash, k_logSubFolderName)};
        m_fileName = fmt::format("{}/{}_{}.txt", logSaveFolder, __ZJ_PKG_NAME__, ZjChrono::getTimeIso());
    } else {
        m_fileName.clear();
    }

    try {
        /// @see https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
        /// @note Using default thread settings, and one thread should be enough for both ZjLog and a few csv logs
        spdlog::init_thread_pool(k_defaultLogThreadQSize, k_defaultLogThreadCount);
        auto stdoutSink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        std::vector<spdlog::sink_ptr> sinks {stdoutSink};

        // If file name is empty, won't create rotating file sink, so no log file will be saved
        if (!m_fileName.empty()) {
            auto rotatingFileSink {std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_fileName, k_maxLogFileSize, k_maxLogNumFiles)};
            sinks.push_back(rotatingFileSink);
        }

        m_logger = std::make_shared<spdlog::async_logger>(
            __ZJ_PKG_NAME__, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    } catch (const std::exception& e) {
        auto errMsg {fmt::format(ZJ_B_RED "Regular log initialization failed, exception [{} | {}]" ZJ_PLAIN, _ZJ_DEMANGLE(e), e.what())};
        printf("%s\n", errMsg.c_str());
    }

    m_logger->flush_on(spdlog::level::info);
    m_logger->set_level(spdlog::level::trace);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // Set time to 3 digits precision after the decimal point
    m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
}

void ZjLog::shutdown()
{
    if (m_logger) {
        m_logger->log(CoreLogLevel::info, "ZjLog shuting down in 3, 2, 1...");
        // Force a flush before shutdown to make sure all messages get logged
        m_logger->flush();
    }

    m_logger.reset();
    spdlog::shutdown();
}
