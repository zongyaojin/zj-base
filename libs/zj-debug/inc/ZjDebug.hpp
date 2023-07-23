#pragma once

#include "ZjExceptions.hpp"
#include "ZjUtilityMacros.hpp"
#include "ZjColors.hpp"
#include "ZjLogAgents.hpp"

#include <cstring>
#include <source_location>
#include <string>
#include <type_traits>

#include <spdlog/spdlog.h>
#include <fmt/format.h>

namespace zj {
namespace debug {
static constexpr const char* k_notFromZj = "NOT_FROM_ZJ_EXCEPTION";
static constexpr const char* k_formatter {"{}:{}:{} @ `{}`; " ZJ_I_WHITE "{}" ZJ_PLAIN};
}
}

template <typename... Args>
void _ZjThrow(const ZjE t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    using namespace zj::debug;

    std::string msg {fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...)};
    std::string fmtMsg {fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    switch (t) {
        case ZjE::Failure: {
            _ZjMessage(ZjLogLevel::Critical, s, fmtMsg);
            throw ZjFailure();
        } break;
        case ZjE::Fault: {
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjFault();
        } break;
        case ZjE::Bug: {
            bool notTopOfChain {std::strcmp(e.what(), k_notFromZj) == 0};
            fmtMsg = notTopOfChain ? fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), "")
                                   : fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(),
                                       fmt::format("external exception [{}, {}] from [{}]", _ZJ_DEMANGLE(e), e.what(), msg));
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjBug("caught external exception, see log trace top for details");
        } break;
        default:
            _ZjAssert("N/A", s, ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN, static_cast<std::uint8_t>(t));
    }
}

#define _ZJ_THROW_EXCEPTION(t, ...)                                                                                                        \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(t), ZjE>, ZJ_B_YELLOW "first argument of `_ZJ_THROW()` has to be an ZjE" ZJ_PLAIN);          \
        static_assert(t != ZjE::Bug, ZJ_B_YELLOW "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions" ZJ_PLAIN);                \
        switch (t) {                                                                                                                       \
            case ZjE::Failure:                                                                                                             \
                _ZjThrow(t, ZjFailure(), std::source_location::current(), ##__VA_ARGS__);                                                  \
                break;                                                                                                                     \
            case ZjE::Fault:                                                                                                               \
                _ZjThrow(t, ZjFault(), std::source_location::current(), ##__VA_ARGS__);                                                    \
                break;                                                                                                                     \
            default:                                                                                                                       \
                _ZjAssert("N/A", std::source_location::current(), ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN,        \
                    static_cast<std::uint8_t>(t));                                                                                         \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_TRY(expression)                                                                                                                \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            expression;                                                                                                                    \
        } catch (const ZjFailure& e) {                                                                                                     \
            _ZjThrow(ZjE::Failure, e, std::source_location::current());                                                                    \
        } catch (const ZjFault& e) {                                                                                                       \
            _ZjThrow(ZjE::Fault, e, std::source_location::current());                                                                      \
        } catch (const ZjBug& e) {                                                                                                         \
            _ZjThrow(ZjE::Bug, ZjBug(zj::debug::k_notFromZj), std::source_location::current());                                            \
        } catch (const std::exception& e) {                                                                                                \
            _ZjThrow(ZjE::Bug, e, std::source_location::current(), std::string {#expression});                                             \
        } catch (...) {                                                                                                                    \
            _ZjAssert("N/A", std::source_location::current(), ZJ_BLUE "unknown exception, package cannot trace it" ZJ_PLAIN);              \
        }                                                                                                                                  \
    } while (0)

// ---------------------------------------------------------
// Convenient wrappers
// ---------------------------------------------------------

#define _ZJ_THROW(...) _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__)
#define _ZJ_THROW_FAILURE(...) _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__)

#define _ZJ_THROW_IF(condition, ...)                                                                                                       \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__);                                                                                \
        }                                                                                                                                  \
    } while (0)

#define _ZJ_THROW_FAILURE_IF(condition, ...)                                                                                               \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__);                                                                              \
        }                                                                                                                                  \
    } while (0)
