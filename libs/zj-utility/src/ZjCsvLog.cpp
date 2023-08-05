#include "ZjCsvLog.hpp"
#include "spdlog/sinks/basic_file_sink.h"

void ZjCsvLog::ZjCsvLogSingleFile::init(const Filename& filename, const DataSize dataSize)
{
    _ZJ_ASSERT(dataSize > 0, "invalid data size");

    m_dataSize = dataSize;
    return;
}

void ZjCsvLog::ZjCsvLogSingleFile::finish()
{
    if (!m_logger) {
        return;
    }

    m_logger->flush();
    m_logger.reset();
}

void ZjCsvLog::finish(const Filename& filename)
{
    return;
}
