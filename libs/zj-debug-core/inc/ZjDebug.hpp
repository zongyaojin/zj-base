/**
 * @file ZjDebug.hpp
 *
 * @brief Debug functions and macros
 *
 * @author Zongyao Jin
 * @date 2023-07-26
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

/// String for exceptions from upstream
static constexpr const char* k_notTopOfChain {"ZJ_NOT_TOP_OF_CHAIN"};

/// Debugging information formatter string
static constexpr const char* k_formatter {"{}:{}:{} @ `{}`; {}"};

} // namespace debug
} // namespace zj

/**
 * @brief Throw a zj-customized exception; @warning Intended to be wrapped by zj macros, not directly used by client
 *
 * @tparam Args Variadic template type
 * @param t Exception type
 * @param e Exception object, could be zj exceptions or std exceptions
 * @param s Source location
 * @param fmt Formatter string
 * @param args Variadic argument for the message
 *
 * @note ZjBug is reserved for catching and re-throwing external, non-zj exceptions
 */
template <typename... Args>
void _ZjThrow(const ZjE t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    using zj::debug::k_formatter;
    using zj::debug::k_notTopOfChain;

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
            /// @note Here we define two cases when throwing a ZjBug, which is reserved for when an external exception is caught; (1) at the
            /// site, top of the call chain, where the external exception is caught, we throw a ZjBug and attached the expression being
            /// evaluated as the error message; (2) because ZjBug is reserved for external exceptions, if we catch a ZjBug at a lower level
            /// of the call chain, we know the error-inducing expression is already logged with an error message when throwing the first
            /// ZjBug; thus we throw another ZjBut with the exception message "k_notTopOfChain", indicating the error message is already
            /// logged, and we attached an empty message to avoid logging the error message more than once
            bool notTopOfChain {std::strcmp(e.what(), k_notTopOfChain) == 0};
            fmtMsg = notTopOfChain ? fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), "")
                                   : fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(),
                                       fmt::format("external exception [{}, {}] from [{}]", _ZJ_DEMANGLE(e), e.what(), msg));
            _ZjMessage(ZjLogLevel::Error, s, fmtMsg);
            throw ZjBug("caught external exception, see log trace top for details");
        } break;
        default:
            _ZjAssert("N/A", s, "illegal exception type [{}], check code logic", static_cast<std::uint8_t>(t));
    }
}

/**
 * @brief A macro that throws with call site source location and a ZjException specified by an input argument
 * @warning Intended to be wrapped with easier-to-use macros, not directly used by client
 */
#define _ZJ_THROW_EXCEPTION(t, ...)                                                                                                        \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(t), ZjE>, "first argument of `_ZJ_THROW()` has to be an ZjE");                               \
        static_assert(t != ZjE::Bug, "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions");                                     \
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

/**
 * @brief A try-catch macro that throws and re-throws zj exception types and provides call site source location, @see _ZjThrow for the two
 * cases for ZjBug and the throwing rules
 */
#define _ZJ_TRY(expression)                                                                                                                \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            expression;                                                                                                                    \
        } catch (const ZjFailure& e) {                                                                                                     \
            _ZjThrow(ZjE::Failure, e, std::source_location::current());                                                                    \
        } catch (const ZjFault& e) {                                                                                                       \
            _ZjThrow(ZjE::Fault, e, std::source_location::current());                                                                      \
        } catch (const ZjBug& e) {                                                                                                         \
            _ZjThrow(ZjE::Bug, ZjBug(zj::debug::k_notTopOfChain), std::source_location::current());                                        \
        } catch (const std::exception& e) {                                                                                                \
            _ZjThrow(ZjE::Bug, e, std::source_location::current(), std::string {#expression});                                             \
        } catch (...) {                                                                                                                    \
            _ZjAssert("N/A", std::source_location::current(), "unknown exception, package cannot trace it");                               \
        }                                                                                                                                  \
    } while (0)

// ---------------------------------------------------------
// Convenient wrappers
// ---------------------------------------------------------

/// Throw ZjFault
#define _ZJ_THROW(...) _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__)

/// Throw ZjFailure
#define _ZJ_THROW_FAILURE(...) _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__)

/// Throw ZjFault if condition is satisfied
#define _ZJ_THROW_IF(condition, ...)                                                                                                       \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Fault, ##__VA_ARGS__);                                                                                \
        }                                                                                                                                  \
    } while (0)

/// Throw ZjFailure if condition is satisfied
#define _ZJ_THROW_FAILURE_IF(condition, ...)                                                                                               \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjE::Failure, ##__VA_ARGS__);                                                                              \
        }                                                                                                                                  \
    } while (0)
