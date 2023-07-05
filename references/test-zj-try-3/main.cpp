#include <iostream>
#include <Eigen/Eigen>

#include "ZjDebug.hpp"
#include "ZjUtility.hpp"

#include <exception>

// replace all spdlog::msg by

/**
 * replace all spdlog::msg by
 *
 * auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
 * my_logger->set_level(spdlog::level::trace);
 *
 * and use that
 */

// ---------------------------------------------------------
ZjRet foobar(int i)
{
    _ZJ_DEBUG(true);

    _ZJ_WARN("{}", _ZJ_DEMANGLE(i));
    _ZJ_WARN("{}", _ZJ_TYPEID(const int&));

    if (i <= 0) {
        return _ZJ_ISSUE(ZJ_ERR, "i should be > 0");
    }

    _ZJ_INFO("i value ok");
    return ZJ_OK;
}

ZjRet func2(int i)
{
    _ZJ_DEBUG(true);

    _ZJ_SCAN(foobar(i));
    return ZJ_OK;
}

// ---------------------------------------------------------

// #define _ZJ_TRY(function)

enum class ZjExceptionType : std::int8_t
{
    Bug = 0,
    Fault,
    Failure,
};

class ZjException : public std::exception
{
public:
    ZjException() = default;
    virtual ~ZjException() noexcept = default;

    ZjException(const std::string& msg)
    : m_msg(msg)
    { }

    virtual const char* what() const noexcept { return m_msg.c_str(); }

protected:
    std::string m_msg;
};

class ZjBug : public ZjException
{
public:
    ZjBug() = default;
    virtual ~ZjBug() noexcept = default;

    ZjBug(const std::string& msg)
    : ZjException(msg)
    { }
};

class ZjFault : public ZjException
{
public:
    ZjFault() = default;
    virtual ~ZjFault() noexcept = default;

    ZjFault(const std::string& msg)
    : ZjException(msg)
    { }
};

class ZjFailure : public ZjException
{
public:
    ZjFailure() = default;
    virtual ~ZjFailure() noexcept = default;

    ZjFailure(const std::string& msg)
    : ZjException(msg)
    { }
};

namespace zj {
namespace debug {
const std::string k_noPrintStr {"ZJ_NO_PRINT"};
}
}

template <typename... Args>
void _ZjThrow(
    ZjExceptionType t, const std::exception& e, const char* file, int line, const char* func, const std::string& fmt = "", Args&&... args)
{
    std::string msg {fmt::format(fmt, std::forward<Args>(args)...)};

    std::string logFmt {
        "----------------------------------------\n"
        "Src: {}:{}:\'{}\'\n"
        "Msg: " CC_B_WHITE "{}\n" CC_RESET};

    std::string fmtMsg {fmt::format(std::move(logFmt), file, line, func, std::move(msg))};

    switch (t) {
        case ZjExceptionType::Failure: {
            spdlog::critical("{}", fmtMsg);
            throw ZjFailure();
        } break;
        case ZjExceptionType::Fault: {
            spdlog::error("{}", fmtMsg);
            throw ZjFault();
        } break;
        case ZjExceptionType::Bug: {
            if (msg.empty()) {
                fmtMsg = std::string {e.what()} == zj::debug::k_noPrintStr
                             ? fmt::format(std::move(logFmt), file, line, func, "")
                             : fmt::format(std::move(logFmt), file, line, func,
                                 fmt::format("std exception, type: [{}], what: [{}]", _ZJ_DEMANGLE(e), e.what()));
            }
            spdlog::error("{}", fmtMsg);
            throw ZjBug("caught std exception, see top error log for more information");
        } break;
        default:
            _ZJ_ASSERT(false, "unknown exception type, [{}]", t);
    }
}

#define _ZJ_THROW(e, ...)                                                                                                                  \
    do {                                                                                                                                   \
        static_assert(e != ZjExceptionType::Bug); /* use type traits to check if error is a ZjExceptionType */                             \
        switch (e) {                                                                                                                       \
            case ZjExceptionType::Failure:                                                                                                 \
                _ZjThrow(e, ZjFailure(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);                                                 \
                break;                                                                                                                     \
            case ZjExceptionType::Fault:                                                                                                   \
                _ZjThrow(e, ZjFault(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);                                                   \
                break;                                                                                                                     \
            default:                                                                                                                       \
                _ZJ_ASSERT(false, "exception type incorrect, code shouldn't reach here, check implementation logic");                      \
        }                                                                                                                                  \
    } while (0)

// no need to chain messages anymore
#define _ZJ_TRY(function)                                                                                                                  \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            function;                                                                                                                      \
        } catch (const ZjFailure& e) {                                                                                                     \
            _ZjThrow(ZjExceptionType::Failure, e, __FILE__, __LINE__, __FUNCTION__);                                                       \
        } catch (const ZjFault& e) {                                                                                                       \
            _ZjThrow(ZjExceptionType::Fault, e, __FILE__, __LINE__, __FUNCTION__);                                                         \
        } catch (const ZjBug& e) {                                                                                                         \
            _ZjThrow(ZjExceptionType::Bug, ZjBug(zj::debug::k_noPrintStr), __FILE__, __LINE__, __FUNCTION__);                              \
        } catch (const std::exception& e) {                                                                                                \
            _ZjThrow(ZjExceptionType::Bug, e, __FILE__, __LINE__, __FUNCTION__);                                                           \
        } catch (...) {                                                                                                                    \
            _ZJ_ASSERT(false, "caught unknown exception, zj-debug package cannot trace it");                                               \
        }                                                                                                                                  \
    } while (0)

class unknown
{ };

void myFunc0()
{
    // throw unknown();
    // throw std::runtime_error("an std run time exception");

    // _ZJ_THROW(ZjExceptionType::Failure, "nested test error source");
    _ZJ_THROW(ZjExceptionType::Fault, "nested test error source");
}

void myFunc1()
{
    spdlog::info("my func 1");
    _ZJ_TRY(myFunc0());
}

void myFunc2()
{
    spdlog::info("my func 2");
    _ZJ_TRY(myFunc1());
}

int myFunc3()
{
    spdlog::info("my func 3");
    _ZJ_TRY(myFunc2());
    return 1;
}

int main()
{
    // throw ZjFailure("hi");

    int i;
    // _ZJ_TRY(i = myFunc3());
    i = myFunc3();

    _ZJ_INFO("{}", i);

    _ZJ_THROW(ZjExceptionType::Fault, "testing {}", 1);

    return 0;
}
