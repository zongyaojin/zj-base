/**
 * @file zj-logger.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "zj-logger.hpp"
#include "zj-colors.hpp"
#include "zj-chrono.hpp"
#include "zj-basic-macros.hpp"

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

} // namespace

void ZjLogger::Log(const ZjLogLevel level, std::string&& msg)
{
    // The current version of cpplint doesn't like it, but it could be `if (logger_) [[unlikely]] {}` with C++ 23 to improve performance
    if (logger_) {
        logger_->log(log_level_map_.at(level), msg);
        return;
    }

    Init();
    logger_->log(log_level_map_.at(level), msg);

    if (level == ZjL::kCritical) {
        // Make sure it flushes the logger if the message is critical
        logger_->flush();
    }
}

void ZjLogger::Init(const std::string& csv_log_folder_no_slash, const std::string& regular_log_folder_no_slash)
{
    if (logger_) {
        return;
    }

    csv_log_folder_no_slash_ = csv_log_folder_no_slash;
    regular_log_folder_no_slash_ = regular_log_folder_no_slash;

    {
        auto regularFolderInfo
            = regular_log_folder_no_slash_.empty()
                  ? fmt::format(ZJ_B_GREEN "ZjLogger not saving regular log to file" ZJ_PLAIN)
                  : fmt::format(ZJ_B_GREEN "ZjLogger sets regular log base folder to [{}]" ZJ_PLAIN, regular_log_folder_no_slash);
        auto csvFolderInfo = csv_log_folder_no_slash_.empty()
                                 ? fmt::format(ZJ_B_GREEN "ZjLogger using default csv log base folder" ZJ_PLAIN)
                                 : fmt::format(ZJ_B_GREEN "ZjLogger sets csv log base folder to [{}]" ZJ_PLAIN, csv_log_folder_no_slash_);

        // Logger not initialized, using raw console print
        printf("[%s | %s]\n", regularFolderInfo.c_str(), csvFolderInfo.c_str());
    }

    // If regular log folder folder is empty, do not create log file, only log to console
    if (!regular_log_folder_no_slash_.empty()) {
        std::string logSaveFolder {fmt::format("{}/{}", regular_log_folder_no_slash_, k_logSubFolderName)};
        filename_ = fmt::format("{}/{}_{}.txt", logSaveFolder, __ZJ_PKG_NAME__, ZjGetTimeIso());
    } else {
        filename_.clear();
    }

    try {
        /// @see https://github.com/gabime/spdlog#asynchronous-logger-with-multi-sinks
        /// @note Using default thread settings, and one thread should be enough for both ZjLogger and a few csv logs
        spdlog::init_thread_pool(k_defaultLogThreadQSize, k_defaultLogThreadCount);
        auto stdoutSink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        std::vector<spdlog::sink_ptr> sinks {stdoutSink};

        // If file name is empty, won't create rotating file sink, so no log file will be saved
        if (!filename_.empty()) {
            auto rotatingFileSink {std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename_, k_maxLogFileSize, k_maxLogNumFiles)};
            sinks.push_back(rotatingFileSink);
        }

        logger_ = std::make_shared<spdlog::async_logger>(
            __ZJ_PKG_NAME__, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    } catch (const std::exception& e) {
        auto err_msg {fmt::format(ZJ_B_RED "Regular log initialization failed, exception [{} | {}]" ZJ_PLAIN, _ZJ_DEMANGLE(e), e.what())};
        printf("%s\n", err_msg.c_str());
    }

    logger_->flush_on(spdlog::level::info);
    logger_->set_level(spdlog::level::trace);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // Set time to 3 digits precision after the decimal point
    logger_->set_pattern("%Y-%m-%d %H:%M:%S.%e | %^%l%$ | %v");
}

void ZjLogger::Shutdown()
{
    if (logger_) {
        logger_->log(CoreLogLevel::info, "ZjLogger shuting down in 3, 2, 1...");
        // Force a flush before shutdown to make sure all messages get logged
        logger_->flush();
    }

    logger_.reset();
    spdlog::shutdown();
}
