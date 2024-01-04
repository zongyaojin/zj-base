/**
 * @file zj-debug.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-exceptions.hpp"
#include "zj-basic-macros.hpp"
#include "zj-colors.hpp"
#include "zj-formatters.hpp"
#include "zj-logging-agents.hpp"

#include <cstring>
#include <source_location>
#include <string>
#include <type_traits>
#include <utility>
#include <cstdio>

#include "spdlog/spdlog.h"
#include "fmt/format.h"

/**
 * @brief A debugging helper that immediately prints without logging; it provides call site trace and takes an optional user message
 *
 * @tparam Args Variadic template type
 * @param[in] s Source location
 * @param[in] fmt Formatter
 * @param[in] args Variadic argument for the message
 *
 * @note This is intended to be used in functions that would run into segmentation fault, yet you don't know which line triggers the fault
 * (e.g., GDB indicates a function causes the segmentation fault, but the function is very long, you don't know which line causes it); by
 * inserting this macro in between lines of the faulty function, it's easy to see until which line the function still runs
 *
 * @warning Client code shouldn't use this function directly, they should use macro _ZJ_PRINT_IF instead
 */
template <typename... Args>
void _ZjPrint(const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string user_msg {fmt::format(fmt::runtime(fmt), args...)};
    if (user_msg.empty()) { user_msg = "N/A"; }

    constexpr const char* colored_fmt {ZJ_B_PURPLE "ZJ-PRINT" ZJ_PLAIN " | " ZJ_B_WHITE "{}:{}:{} @ `{}`" ZJ_PLAIN " | {}\n"};
    std::string fmt_msg {fmt::format(colored_fmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(user_msg))};
    printf("%s\n", fmt_msg.c_str());
}

/// A macro wrapper for _ZjPrint that provides in-place source location for call site tracing
#define _ZJ_PRINT_IF(enabled, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(enabled);                                                                                                 \
        if (enabled) { _ZjPrint(std::source_location::current(), ##__VA_ARGS__); }                                                         \
    } while (0)

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
 * @param[in] t Exception type
 * @param[in] e Exception object, could be zj exceptions or std exceptions
 * @param[in] s Source location
 * @param[in] fmt Formatter string
 * @param[in] args Variadic argument for the message
 */
template <typename... Args>
void _ZjThrow(const ZjE t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    std::string msg {fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...)};
    std::string fmt_msg {fmt::format(zj::kTraceFmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    switch (t) {
        case ZjE::kFailure: {
            _ZjMessage(ZjLogLevel::kCritical, s, fmt_msg);
            throw ZjFailure(e.what());
        } break;
        case ZjE::kFault: {
            _ZjMessage(ZjLogLevel::kError, s, fmt_msg);
            throw ZjFault(e.what());
        } break;
        case ZjE::kSingularity: {
            _ZjMessage(ZjLogLevel::kError, s, fmt_msg);
            throw ZjSingularity(e.what());
        } break;
        case ZjE::kBug: {
            _ZjMessage(ZjLogLevel::kError, s, fmt_msg);
            throw ZjBug(e.what());
        } break;
        default: _ZjAssert("N/A", s, "invalid exception type [{}], check code logic", static_cast<std::uint8_t>(t));
    }
}

/**
 * @brief A try-catch macro that throws and re-throws zj exception types and provides call site source location
 *
 * @note For the time being, Boost::stacktrace provides similar functionalities but the output information isn't as good as expected; it
 * takes a lot of platform-dependent compile option to make the stacktrace to print files and line numbers, and sometime the information is
 * still incomplete
 * @see https://www.boost.org/doc/libs/1_83_0/doc/html/stacktrace.html
 *
 * @note Once most compilers have the <stacktrace> proposed in C++ 23 implemented, we should give that a try; currently, at the moment, even
 * the latest major compilers don't have it
 * @see https://en.cppreference.com/w/cpp/utility/basic_stacktrace
 *
 * @warning Macros are not very smart when dealing with expressions with commas; try to avoid writing expressions such as `v << 1, 2, 3;`
 * with macros, if you have to, consider wrapping the expression with parentheses or brackets; or use the standard try-catch clause
 */
#define _ZJ_TRY(expression)                                                                                                                \
    try {                                                                                                                                  \
        expression;                                                                                                                        \
    } catch (const ZjFailure& e) {                                                                                                         \
        _ZjThrow(ZjE::kFailure, e, std::source_location::current());                                                                       \
    } catch (const ZjFault& e) {                                                                                                           \
        _ZjThrow(ZjE::kFault, e, std::source_location::current());                                                                         \
    } catch (const ZjSingularity& e) {                                                                                                     \
        _ZjThrow(ZjE::kSingularity, e, std::source_location::current());                                                                   \
    } catch (const ZjBug& e) {                                                                                                             \
        _ZjThrow(ZjE::kBug, e, std::source_location::current());                                                                           \
    } catch (const std::exception& e) {                                                                                                    \
        auto s {std::source_location::current()};                                                                                          \
        auto err_msg {fmt::format("external exception, type [{}], what [{}], from [{}]", _ZJ_DEMANGLE(e), e.what(), #expression)};         \
        auto fmt_msg {fmt::format(zj::kTraceFmt, s.file_name(), s.line(), s.column(), s.function_name(), std::move(err_msg))};             \
        _ZjThrow(ZjE::kBug, ZjBug(std::move(fmt_msg)), std::source_location::current());                                                   \
    } catch (...) {                                                                                                                        \
        _ZjAssert("N/A", std::source_location::current(), "unknown exception, package cannot trace it");                                   \
    }

/**
 * @brief A macro that throws with call site source location and a ZjException specified by an input argument
 * @warning Intended to be wrapped with easier-to-use macros, not directly used by client
 */
#define _ZJ_THROW_EXCEPTION(t, ...)                                                                                                        \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(t), ZjE>, "first argument of `_ZJ_THROW()` has to be a ZjExceptionType");                    \
        static_assert(t != ZjE::kBug, "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions");                                    \
        static_assert(t != ZjE::kSingularity, "ZjSingularity is reserved for `_ZJ_VERIFY()` to check numerics");                           \
        switch (t) {                                                                                                                       \
            case ZjE::kFailure: _ZjThrow(t, ZjFailure(), std::source_location::current(), ##__VA_ARGS__); break;                           \
            case ZjE::kFault: _ZjThrow(t, ZjFault(), std::source_location::current(), ##__VA_ARGS__); break;                               \
            default:                                                                                                                       \
                _ZjAssert("N/A", std::source_location::current(), "illegal exception type [{}], check code logic",                         \
                    static_cast<std::uint8_t>(t));                                                                                         \
        }                                                                                                                                  \
    } while (0)

// ---------------------------------------------------------
// Convenient wrappers
// ---------------------------------------------------------

/// Throw ZjFault
#define _ZJ_THROW(...) _ZJ_THROW_EXCEPTION(ZjE::kFault, ##__VA_ARGS__)

/// Throw ZjFailure
#define _ZJ_THROW_FAILURE(...) _ZJ_THROW_EXCEPTION(ZjE::kFailure, ##__VA_ARGS__)

/// @brief Throw ZjFault if condition not satisfied
/// @note No need to log the condition since source location will take client to the call site where the condition is present
#define _ZJ_THROW_IF(condition, ...)                                                                                                       \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) { _ZJ_THROW_EXCEPTION(ZjE::kFault, ##__VA_ARGS__); }                                                              \
    } while (0)

/// @brief Throw ZjFailure if condition not satisfied, @see Notes in _ZJ_THROW_IF
#define _ZJ_THROW_FAILURE_IF(condition, ...)                                                                                               \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) { _ZJ_THROW_EXCEPTION(ZjE::kFailure, ##__VA_ARGS__); }                                                            \
    } while (0)
