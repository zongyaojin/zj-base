#pragma once

#include "ZjExceptions.hpp"
#include "ZjTypeFinders.hpp"
#include "ZjColors.hpp"
#include "ZjLogAgent.hpp"

#include <cstring>
#include <source_location>
#include <string>
#include <type_traits>

#include <spdlog/spdlog.h>
#include <fmt/format.h>

namespace zj {
namespace trial {
static constexpr const char* k_notFromZj = "NOT_FROM_ZJ_EXCEPTION";
static constexpr const char* k_formatter {"{}:{}:{} @ `{}` | " ZJ_I_WHITE "{}" ZJ_PLAIN};
}
}

template <typename... Args>
void _ZjThrow(const ZjEt t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    using namespace zj::trial;

    std::string msg {fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...)};
    std::string fmtMsg {fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    switch (t) {
        case ZjEt::Failure: {
            spdlog::critical("{}", fmtMsg);
            throw ZjFailure();
        } break;
        case ZjEt::Fault: {
            spdlog::error("{}", fmtMsg);
            throw ZjFault();
        } break;
        case ZjEt::Bug: {
            if (msg.empty()) {
                bool notTopOfChain = std::strcmp(e.what(), k_notFromZj) == 0;
                fmtMsg = notTopOfChain ? fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), "")
                                       : fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(),
                                           fmt::format("upstream exception [{} | {}]", _ZJ_DEMANGLE(e), e.what()));
            }
            spdlog::error("{}", fmtMsg);
            throw ZjBug("caught upstream exception, see log trace for details");
        } break;
        default:
            _ZjAssert("N/A", s, ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN, static_cast<std::uint8_t>(t));
    }
}

#define _ZJ_THROW(e, ...)                                                                                                                  \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(e), ZjEt>, ZJ_B_YELLOW "first argument of `_ZJ_THROW()` has to be an ZjEt" ZJ_PLAIN);        \
        static_assert(e != ZjEt::Bug, ZJ_B_YELLOW "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions" ZJ_PLAIN);               \
        switch (e) {                                                                                                                       \
            case ZjEt::Failure:                                                                                                            \
                _ZjThrow(e, ZjFailure(), std::source_location::current(), ##__VA_ARGS__);                                                  \
                break;                                                                                                                     \
            case ZjEt::Fault:                                                                                                              \
                _ZjThrow(e, ZjFault(), std::source_location::current(), ##__VA_ARGS__);                                                    \
                break;                                                                                                                     \
            default:                                                                                                                       \
                _ZjAssert("N/A", std::source_location::current(), ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN,        \
                    static_cast<std::uint8_t>(e));                                                                                         \
        }                                                                                                                                  \
    } while (0)
