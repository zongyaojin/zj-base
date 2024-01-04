/**
 * @file zj-csv-logger.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "zj-csv-logger.hpp"
#include "zj-chrono.hpp"
#include "zj-logging-macros-simplified.hpp"
#include "zj-logger.hpp"

#include "fmt/format.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace {
static constexpr const char* k_csvLogFolderName {"zj-csv-logs"};
}

void ZjCsvLogger::ZjCsvLoggingUnit::Init(const std::string& log_name, const DataSize data_size)
{
    // This will take care of spdlog thread initialization, if it's already initialized, it will do nothing
    ZjLogger::GetInstance().Init();

    log_name_ = log_name;
    data_size_ = data_size;
    _ZJ_THROW_IF(log_name_.empty(), "empty log name");
    _ZJ_THROW_IF(data_size_ < 1, "invalid data size [{}]", data_size_);

    std::string logSaveFolder = ZjLogger::GetInstance().CsvLogFolder().empty()
                                    ? fmt::format("{}/{}", __ZJ_PKG_BUILD_PATH_NO_SLASH__, k_csvLogFolderName)
                                    : fmt::format("{}/{}", ZjLogger::GetInstance().CsvLogFolder(), k_csvLogFolderName);

    filename_ = fmt::format("{}/{}_{}.csv", logSaveFolder, log_name_, ZjGetTimeIso());

    _ZJ_TRY(logger_ = spdlog::basic_logger_mt(log_name_, filename_, true));
    _ZJ_THROW_IF(!logger_, "failed to initialize logger [{}]", log_name_);

    /// @note No need to flush every once in a while since the logger is initialized to flush on info level, and all messages are logged at
    /// the same level; i.e., they will be logged and flushed at the same time, no information would be lost
    /// @note This also means if ZjLogger shuts down the spdlog when the whole program terminates, this csv log should have all information
    /// already flushed to the file, there shouldn't be any problem
    logger_->flush_on(spdlog::level::info);
    logger_->set_level(spdlog::level::info);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // Formatted as seconds since epoch, dot, microsecond part of the current second
    logger_->set_pattern("%E.%f, %v");

    _ZJ_INFO("ZjCsvLoggingUnit starts [{}]", log_name_);
}

// ---------------------------------------------------------

void ZjCsvLogger::Drop(const std::string& log_name)
{
    auto it = logging_units_.find(log_name);

    if (it != logging_units_.end()) { logging_units_.erase(it); }
}

std::string ZjCsvLogger::Filename(const std::string& log_name)
{
    if (logging_units_.find(log_name) != logging_units_.end()) { return logging_units_.at(log_name).Filename(); }

    return std::string {};
}
