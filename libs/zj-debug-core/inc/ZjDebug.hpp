/**
 * @file ZjDebug.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "ZjExceptions.hpp"
#include "ZjBasicMacros.hpp"
#include "ZjColors.hpp"
#include "ZjLogAgents.hpp"

#include <cstring>
#include <source_location>
#include <string>
#include <type_traits>
#include <utility>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace zj {
namespace debug {

/// Debugging information formatter string
static constexpr const char* k_formatter {"{}:{}:{} @ `{}` | {}"};

} // namespace debug
} // namespace zj

/**
 * @brief Throw a zj-customized exception
 *
 * @note ZjBug is reserved for catching and re-throwing external, non-zj exceptions
 *
 * @warning This function is intended to be wrapped by zj macros, not directly used by client; client code should use the macros
 * @warning There's an known issue. If _ZjThrow or any of the `_ZJ_THROW*` macros is used to as the one and only thing is a program
 * to throw an exception without being caught. The program will terminate (expected); yet the error message may or may not be logged. Not
 * sure why even if the logger's `flush()` is explicitly called in between calling _ZjMessage to log the message and throwing the exception.
 * I think it may due to `spdlog` creates a async thread, yet the program in this case terminates too fast to the thread to handle the
 * logging. However, since the error message is written to the exception, the exception `what()` message can still help display the error
 * message.
 *
 * @tparam Args Variadic template type
 * @param t Exception type
 * @param e Exception object, could be zj exceptions or std exceptions
 * @param s Source location
 * @param fmt Formatter string
 * @param args Variadic argument for the message
 */
template <typename... Args>
void _ZjThrow(const ZjE t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    using zj::debug::k_formatter;

    std::string msg {fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...)};
    std::string fmtMsg {fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    switch (t) {
        case ZjE::Failure: {
            _ZjMessage(ZjLogLevel::Critical, s, fmtMsg);
            throw ZjFailure(e.what());
        } break;
        case ZjE::Fault: {
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjFault(e.what());
        } break;
        case ZjE::Singular: {
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjSingular(e.what());
        } break;
        case ZjE::Bug: {
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjBug(e.what());
        } break;
        default:
            _ZjAssert("N/A", s, "invalid exception type [{}], check code logic", static_cast<std::uint8_t>(t));
    }
}

/**
 * @brief A try-catch macro that throws and re-throws zj exception types and provides call site source location
 */
#define _ZJ_TRY(expression)                                                                                                                \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            expression;                                                                                                                    \
        } catch (const ZjFailure& e) {                                                                                                     \
            _ZjThrow(ZjE::Failure, e, std::source_location::current());                                                                    \
        } catch (const ZjFault& e) {                                                                                                       \
            _ZjThrow(ZjE::Fault, e, std::source_location::current());                                                                      \
        } catch (const ZjSingular& e) {                                                                                                    \
            _ZjThrow(ZjE::Singular, e, std::source_location::current());                                                                   \
        } catch (const ZjBug& e) {                                                                                                         \
            _ZjThrow(ZjE::Bug, e, std::source_location::current());                                                                        \
        } catch (const std::exception& e) {                                                                                                \
            auto s {std::source_location::current()};                                                                                      \
            auto errMsg {fmt::format("external exception, type [{}], what [{}], from [{}]", _ZJ_DEMANGLE(e), e.what(), #expression)};      \
            auto fmtMsg {fmt::format(zj::debug::k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), std::move(errMsg))};  \
            _ZjThrow(ZjE::Bug, ZjBug(std::move(fmtMsg)), std::source_location::current());                                                 \
        } catch (...) {                                                                                                                    \
            _ZjAssert("N/A", std::source_location::current(), "unknown exception, package cannot trace it");                               \
        }                                                                                                                                  \
    } while (0)

/**
 * @brief A macro that throws with call site source location and a ZjException specified by an input argument
 * @warning Intended to be wrapped with easier-to-use macros, not directly used by client
 */
#define _ZJ_THROW_EXCEPTION(t, ...)                                                                                                        \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(t), ZjE>, "first argument of `_ZJ_THROW()` has to be a ZjExceptionType");                    \
        static_assert(t != ZjE::Bug, "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions");                                     \
        static_assert(t != ZjE::Singular, "ZjSingular is reserved for `_ZJ_CHECK()` to check numerics");                                   \
        switch (t) {                                                                                                                       \
            case ZjE::Failure:                                                                                                             \
                _ZjThrow(t, ZjFailure(), std::source_location::current(), ##__VA_ARGS__);                                                  \
                break;                                                                                                                     \
            case ZjE::Fault:                                                                                                               \
                _ZjThrow(t, ZjFault(), std::source_location::current(), ##__VA_ARGS__);                                                    \
                break;                                                                                                                     \
            default:                                                                                                                       \
                _ZjAssert("N/A", std::source_location::current(), "illegal exception type [{}], check code logic",                         \
                    static_cast<std::uint8_t>(t));                                                                                         \
        }                                                                                                                                  \
    } while (0)

// ---------------------------------------------------------
// Convenient wrappers
// ---------------------------------------------------------

/// Throw ZjFault
#define _ZJ_THROW(...) _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__)

/// Throw ZjFailure
#define _ZJ_THROW_FAILURE(...) _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__)

/// @brief Throw ZjFault if condition not satisfied
/// @note No need to log the condition since source location will take client to the call site where the condition is present
#define _ZJ_THROW_IF(condition, ...)                                                                                                       \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__);                                                                                \
        }                                                                                                                                  \
    } while (0)

/// @brief Throw ZjFailure if condition not satisfied, @see Notes in _ZJ_THROW_IF
#define _ZJ_THROW_FAILURE_IF(condition, ...)                                                                                               \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__);                                                                              \
        }                                                                                                                                  \
    } while (0)
