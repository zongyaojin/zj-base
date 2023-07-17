#include "ZjLog.hpp"
#include <iostream>

void ZjLog::log(const ZjLogLevel level, std::string&& msg)
{
    if (!m_logger) {
        m_logger = spdlog::stdout_color_mt("console-colored");

        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
        m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");
        m_logger->set_level(spdlog::level::trace);
    }

    m_logger->log(mk_logLevelMap.at(level), msg);
}