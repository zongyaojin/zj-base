#pragma once

#include "ZjExceptions.hpp"
#include "ZjLog.hpp"
#include "ZjColors.hpp"
#include "ZjTypeFinders.hpp"

#include <source_location>
#include <string>
#include <fmt/format.h>

namespace zj {
namespace throwing {
static const std::string k_noPrint {"NO_PRINT_FOR_EXTERNAL_ERROR"};
}
}

template <typename... Args>
void _ZjThrow(
    const ZjEt t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    ZjLog::getInstance().info(fmt::format(
        "{}:{}:{} @ " ZJ_I_WHITE "\u2018{}\u2019" ZJ_NO_COLOR, s.file_name(), s.line(), s.column(), s.function_name()));

    std::string msg {fmt::format(fmt, std::forward<Args>(args)...)};
    std::string logFmt {"{}:{}:{} @ `{}` | " ZJ_I_WHITE "{}" ZJ_NO_COLOR};
    std::string fmtMsg {
        fmt::format(std::move(logFmt), s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    switch (t) {
        case ZjEt::Failure: {
            ZjLog::getInstance().critical(fmtMsg);
            throw ZjFailure();
        } break;
        case ZjEt::Fault: {
            ZjLog::getInstance().error(fmtMsg);
            throw ZjFault();
        } break;
        case ZjEt::Bug: {
            if (msg.empty()) {
                fmtMsg
                    = std::string {e.what()} == zj::throwing::k_noPrint
                          ? fmt::format(std::move(logFmt), s.file_name(), s.line(), s.column(), s.function_name(), "")
                          : fmt::format(std::move(logFmt), s.file_name(), s.line(), s.column(), s.function_name(),
                              fmt::format("upstream exception [{} | {}]", _ZJ_DEMANGLE(e), e.what()));
            }
            ZjLog::getInstance().error(fmtMsg);
            throw ZjBug("caught upstream exception, see top error log for details");
        } break;
        default:
            _ZJ_ASSERT(false, "unknown exception type [{}]", t);
    }
}