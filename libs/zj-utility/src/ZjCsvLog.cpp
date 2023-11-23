/**
 * @file ZjCsvLog.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "ZjCsvLog.hpp"
#include "zj-chrono.hpp"
#include "zj-logging-macros-simplified.hpp"
#include "zj-logger.hpp"

#include "fmt/format.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace {
static constexpr const char* k_csvLogFolderName {"zj-csv-logs"};
}

void ZjCsvLog::ZjCsvLogWorker::init(const std::string& logName, const DataSize dataSize)
{
    // This will take care of spdlog thread initialization, if it's already initialized, it will do nothing
    ZjLogger::GetInstance().Init();

    m_logName = logName;
    m_dataSize = dataSize;
    _ZJ_THROW_IF(m_logName.empty(), "empty log name");
    _ZJ_THROW_IF(m_dataSize < 1, "invalid data size [{}]", m_dataSize);

    std::string logSaveFolder = ZjLogger::GetInstance().CsvLogFolder().empty()
                                    ? fmt::format("{}/{}", __ZJ_PKG_BUILD_PATH_NO_SLASH__, k_csvLogFolderName)
                                    : fmt::format("{}/{}", ZjLogger::GetInstance().CsvLogFolder(), k_csvLogFolderName);

    filename_ = fmt::format("{}/{}_{}.csv", logSaveFolder, m_logName, ZjGetTimeIso());

    _ZJ_TRY(logger_ = spdlog::basic_logger_mt(m_logName, filename_, true));
    _ZJ_THROW_IF(!logger_, "failed to initialize logger [{}]", m_logName);

    /// @note No need to flush every once in a while since the logger is initialized to flush on info level, and all messages are logged at
    /// the same level; i.e., they will be logged and flushed at the same time, no information would be lost
    /// @note This also means if ZjLogger shuts down the spdlog when the whole program terminates, this csv log should have all information
    /// already flushed to the file, there shouldn't be any problem
    logger_->flush_on(spdlog::level::info);
    logger_->set_level(spdlog::level::info);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // Formatted as seconds since epoch, dot, microsecond part of the current second
    logger_->set_pattern("%E.%f, %v");

    _ZJ_INFO("ZjCsvLogWorker starts [{}]", m_logName);
}

// ---------------------------------------------------------

void ZjCsvLog::drop(const std::string& logName)
{
    auto it = m_logWorkerMap.find(logName);

    if (it != m_logWorkerMap.end()) {
        m_logWorkerMap.erase(it);
    }
}

std::string ZjCsvLog::Filename(const std::string& logName)
{
    if (m_logWorkerMap.find(logName) != m_logWorkerMap.end()) {
        return m_logWorkerMap.at(logName).Filename();
    }

    return std::string {};
}
