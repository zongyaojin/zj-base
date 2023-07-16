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
static constexpr const char* k_formatter {"{}:{}:{} @ `{}`; " ZJ_I_WHITE "{}" ZJ_PLAIN};
}
}

/**
 * @brief
 *
 * @tparam Args
 * @param t
 * @param e
 * @param s
 * @param fmt
 * @param args
 */
template <typename... Args>
void _ZjThrow(const ZjEt t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    using namespace zj::trial;

    std::string msg {fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...)};
    std::string fmtMsg {fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), std::move(msg))};

    // replace spdlog with the log agent

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
            bool notTopOfChain {std::strcmp(e.what(), k_notFromZj) == 0};
            fmtMsg = notTopOfChain ? fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(), "")
                                   : fmt::format(k_formatter, s.file_name(), s.line(), s.column(), s.function_name(),
                                       fmt::format("external exception [{}, {}] from [{}]", _ZJ_DEMANGLE(e), e.what(), msg));
            spdlog::error("{}", fmtMsg);
            throw ZjBug("caught external exception, see log trace top for details");
        } break;
        default:
            _ZjAssert("N/A", s, ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN, static_cast<std::uint8_t>(t));
    }
}

/**
 * @brief
 *
 */
#define _ZJ_THROW_EXCEPTION(t, ...)                                                                                                        \
    do {                                                                                                                                   \
        static_assert(std::is_same_v<decltype(t), ZjEt>, ZJ_B_YELLOW "first argument of `_ZJ_THROW()` has to be an ZjEt" ZJ_PLAIN);        \
        static_assert(t != ZjEt::Bug, ZJ_B_YELLOW "ZjBug is reserved for `_ZJ_TRY()` to pass upstream exceptions" ZJ_PLAIN);               \
        switch (t) {                                                                                                                       \
            case ZjEt::Failure:                                                                                                            \
                _ZjThrow(t, ZjFailure(), std::source_location::current(), ##__VA_ARGS__);                                                  \
                break;                                                                                                                     \
            case ZjEt::Fault:                                                                                                              \
                _ZjThrow(t, ZjFault(), std::source_location::current(), ##__VA_ARGS__);                                                    \
                break;                                                                                                                     \
            default:                                                                                                                       \
                _ZjAssert("N/A", std::source_location::current(), ZJ_BLUE "illegal exception type [{}], check code logic" ZJ_PLAIN,        \
                    static_cast<std::uint8_t>(t));                                                                                         \
        }                                                                                                                                  \
    } while (0)

/**
 * @brief
 *
 */
#define _ZJ_THROW(...) (_ZJ_THROW_EXCEPTION(ZjEt::Fault, ##__VA_ARGS__))

/**
 * @brief
 *
 */
#define _ZJ_THROW_CRITICAL(...) (_ZJ_THROW_EXCEPTION(ZjEt::Critical, ##__VA_ARGS__))

/**
 * @brief
 *
 */
#define _ZJ_THROW_IF(condition, ...)                                                                                                       \
    do {                                                                                                                                   \
        _ZJ_STATIC_CHECK_BOOLEAN(condition);                                                                                                \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjEt::Fault, ##__VA_ARGS__);                                                                               \
        }                                                                                                                                  \
    } while (0)

/**
 * @brief
 *
 */
#define _ZJ_THROW_CRITICAL_IF(condition, ...)                                                                                              \
    do {                                                                                                                                   \
        _ZJ_STATIC_CHECK_BOOLEAN(condition);                                                                                                \
        if ((condition)) {                                                                                                                 \
            _ZJ_THROW_EXCEPTION(ZjEt::Critical, ##__VA_ARGS__);                                                                            \
        }                                                                                                                                  \
    } while (0)

/**
 * @brief
 *
 */
#define _ZJ_TRY(expression)                                                                                                                \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            expression;                                                                                                                    \
        } catch (const ZjFailure& e) {                                                                                                     \
            _ZjThrow(ZjEt::Failure, e, std::source_location::current());                                                                   \
        } catch (const ZjFault& e) {                                                                                                       \
            _ZjThrow(ZjEt::Fault, e, std::source_location::current());                                                                     \
        } catch (const ZjBug& e) {                                                                                                         \
            _ZjThrow(ZjEt::Bug, ZjBug(zj::trial::k_notFromZj), std::source_location::current());                                           \
        } catch (const std::exception& e) {                                                                                                \
            _ZjThrow(ZjEt::Bug, e, std::source_location::current(), std::string {#expression});                                            \
        } catch (...) {                                                                                                                    \
            _ZjAssert("N/A", std::source_location::current(), ZJ_BLUE "unknown exception, package cannot trace it" ZJ_PLAIN);              \
        }                                                                                                                                  \
    } while (0)
