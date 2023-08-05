#include "ZjCsvDynamicLog.hpp"
#include "ZjChrono.hpp"
#include "ZjLogMacrosExtension.hpp"
#include "ZjLog.hpp"

#include "spdlog/sinks/basic_file_sink.h"

namespace {

static constexpr const char* k_csvLogFolderName {"zj-csv-logs"};

}

ZjCsvDynamicLog::ZjCsvDynamicLogWorker::ZjCsvDynamicLogWorker(const std::string& logName, const DataSize dataSize)
: m_dataSize(dataSize)
{
    ZjLog::getInstance().init();
    _ZJ_THROW_IF(m_dataSize < 1, "invalid data size [{}]", m_dataSize);

    m_fileName = fmt::format("{}{}/{}_{}.csv", __ZJ_PKG_BUILD_PATH__, k_csvLogFolderName, logName, ZjChrono::getTimeIso());

    m_logger = spdlog::basic_logger_mt(logName, m_fileName, true);
    _ZJ_THROW_IF(!m_logger, "failed to initialize logger [{}]", logName);

    /// @note No need to flush here since the logger is initialized to flush on info level, and all messages are logged at the same level;
    /// i.e., they will be logged and flushed at the same time, no information would be lost
    /// @note This also means if ZjLog shuts down the spdlog when the whole program terminates, this csv log should have all information
    /// already flushed to the file, there shouldn't be any problem
    m_logger->flush_on(spdlog::level::info);
    m_logger->set_level(spdlog::level::info);

    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // Formatted as seconds since epoch, dot, microsecond part of the current second
    m_logger->set_pattern("%E.%f, %v");

    _ZJ_INFO("ZjCsvDynamicLog started [{}]", m_logger->name());
}

void ZjCsvDynamicLog::drop(const std::string& logName)
{
    auto it = m_logWorkerMap.find(logName);

    if (it != m_logWorkerMap.end()) {
        m_logWorkerMap.erase(it);
    }
}
std::string ZjCsvDynamicLog::fileName(const std::string& logName)
{
    if (m_logWorkerMap.find(logName) != m_logWorkerMap.end()) {
        return m_logWorkerMap.at(logName).fileName();
    }

    return std::string {};
}
