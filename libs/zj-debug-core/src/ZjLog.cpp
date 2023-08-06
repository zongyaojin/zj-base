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
                  : fmt::format(ZJ_B_GREEN "ZjLog sets regular log folder root to [{}]" ZJ_PLAIN, m_regularLogFolderNoSlash);
        auto csvFolderInfo = m_csvLogFolderNoSlash.empty()
                                 ? fmt::format(ZJ_B_GREEN "ZjLog using default csv log folder root" ZJ_PLAIN)
                                 : fmt::format(ZJ_B_GREEN "ZjLog sets csv log folder root to [{}]" ZJ_PLAIN, m_csvLogFolderNoSlash);

        printf("\n\t%s\n", regularFolderInfo.c_str());
        printf("\t%s\n\n", csvFolderInfo.c_str());
    }

    if (!m_regularLogFolderNoSlash.empty()) {
        std::string logSaveFolder {fmt::format("{}/{}", m_regularLogFolderNoSlash, k_logFolderName)};
        m_fileName = fmt::format("{}/{}_{}.txt", logSaveFolder, __ZJ_PKG_NAME__, ZjChrono::getTimeIso());
    } else {
        m_fileName.clear();
    }

    try {
        /// @see https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
        /// @note Using default thread settings, and one thread should be enough for both ZjLog and a few csv logs
        spdlog::init_thread_pool(k_defaultQSize, k_defaultThreadCount);
        auto stdoutSink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        std::vector<spdlog::sink_ptr> sinks {stdoutSink};

        if (!m_fileName.empty()) {
            auto rotatingFileSink {std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_fileName, k_maxFileSize, k_maxNumFiles)};
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
    m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");
}

void ZjLog::shutdown()
{
    if (m_logger) {
        m_logger->log(CoreLogLevel::info, "ZjLog shuting down in 3, 2, 1...");
        // since logger is set to flush only on info level, this forces a flush before shutdown to make sure all messages get logged
        m_logger->flush();
    }

    m_logger.reset();
    spdlog::shutdown();
}
