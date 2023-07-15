#include "ZjLog.hpp"
#include <spdlog/spdlog.h>

void ZjLog::info(const std::string& msg)
{
    spdlog::info(msg);
}

void ZjLog::warn(const std::string& msg)
{
    spdlog::warn(msg);
}

void ZjLog::fault(const std::string& msg)
{
    spdlog::error(msg);
}

void ZjLog::failure(const std::string& msg)
{
    spdlog::critical(msg);
}
