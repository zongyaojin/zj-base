/**
 * @file zj-logger.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-singleton.hpp"

#include <unordered_map>
#include <memory>
#include <string>

#include "spdlog/spdlog.h"

/// Zj log level type enum
enum class ZjLogLevel : std::uint8_t
{
    kTrace = 0,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kCritical,
    kOff,
};

/// Zj log level short alias
using ZjL = ZjLogLevel;

/// @brief ZjLogger singleton class; @warning This class should NOT use any of the debugging or logging macros, since they rely on
/// ZjLogAgents, which relies on this class to actually log information, using those macros in this class would cause "circular reference"
class ZjLogger : public ZjSingleton<ZjLogger>
{
public:
    using CoreLogLevel = spdlog::level::level_enum;
    using CoreLogPtr = std::shared_ptr<spdlog::logger>;

public:
    /**
     * @brief Log a message with specified log level; it will start the spdlog thread if it's not already started
     * @param level Log level
     * @param msg Log message
     */
    void Log(const ZjLogLevel level, std::string&& msg);

    /**
     * @brief Initialize ZjLogger and the spdlog thread, which means this should be initialized before any logging
     *
     * @param csv_log_folder_no_slash Csv log file save folder
     * @param regular_log_folder_no_slash Regular log file save folder
     *
     * @note If csv log folder is empty, csv log files will be saved to this package's build folder
     * @note If regular log folder is empty, regular log will only be printed in the console, no file will be saved
     */
    void Init(const std::string& csv_log_folder_no_slash = "", const std::string& regular_log_folder_no_slash = "");

    /// Shut down ZjLogger and the entire spdlog thread, which means this should be called only when the whole program terminates
    void Shutdown();

    /// Log file name
    inline const std::string& Filename() const { return filename_; }

    /// Regular log folder w/o trailing slash
    inline const std::string& RegularLogFolder() const { return regular_log_folder_no_slash_; }

    /// Csv log folder w/o trailing slash
    inline const std::string& CsvLogFolder() const { return csv_log_folder_no_slash_; }

private:
    /// Log implementation pointer
    CoreLogPtr logger_;

    /// Regular log file name
    std::string filename_;

    /// Zj log level to implementation's log level map
    const std::unordered_map<ZjLogLevel, CoreLogLevel> log_level_map_ {
        {ZjL::kTrace, CoreLogLevel::trace},
        {ZjL::kDebug, CoreLogLevel::debug},
        {ZjL::kInfo, CoreLogLevel::info},
        {ZjL::kWarn, CoreLogLevel::warn},
        {ZjL::kError, CoreLogLevel::err},
        {ZjL::kCritical, CoreLogLevel::critical},
        {ZjL::kOff, CoreLogLevel::off},
    };

    /// User provided csv log and regular log folder
    std::string csv_log_folder_no_slash_, regular_log_folder_no_slash_;
};
