#pragma once

#include <source_location>
#include <string>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace zj {
namespace log {
namespace agent {
static constexpr const char* k_assertFmt {"{}:{}:{} @ `{}` || " ZJ_B_CYAN "[{}]" ZJ_PLAIN "\n{}\n" ZJ_PLAIN};
}
}
}

template <typename... Args>
void _ZjAssert(const char* condition, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string userMsg {fmt::format(fmt::runtime(fmt), args...)};
    spdlog::critical(zj::log::agent::k_assertFmt, s.file_name(), s.line(), s.column(), s.function_name(), condition, std::move(userMsg));
    std::abort();
}