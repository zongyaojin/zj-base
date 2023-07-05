#include <iostream>
#include <Eigen/Eigen>

#include "ZjDebug.hpp"
#include "ZjUtility.hpp"

#include <exception>

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
    Error = 1,
    Critical,
};

class ZjError : public std::exception
{
public:
    ZjError() = default;
    virtual ~ZjError() noexcept = default;

    ZjError(const std::string& msg)
    : m_msg(msg)
    { }

    virtual const char* what() const noexcept { return m_msg.c_str(); }

private:
    std::string m_msg;
};

class ZjCritical : public std::exception
{
public:
    ZjCritical() = default;
    virtual ~ZjCritical() noexcept = default;

    ZjCritical(const std::string& msg)
    : m_msg(msg)
    { }

    virtual const char* what() const noexcept { return m_msg.c_str(); }

private:
    std::string m_msg;
};

template <typename... Args>
void _ZjThrow(ZjExceptionType e, const char* file, int line, const char* func, const std::string& fmt = "", Args&&... args)
{
    std::string msg {fmt::format(fmt, std::forward<Args>(args)...)};

    std::string logFmt {
        "----------------------------------------\n"
        "Src: {}:{}:\'{}\'\n"
        "Msg: " CC_B_WHITE "{}\n" CC_RESET};

    std::string fmtMsg {fmt::format(std::move(logFmt), file, line, func, std::move(msg))};

    switch (e) {
        case ZjExceptionType::Critical: {
            spdlog::critical("{}", fmtMsg);
            throw ZjCritical(msg);
        } break;
        case ZjExceptionType::Error: {
            spdlog::error("{}", fmtMsg);
            throw ZjError(msg);
        } break;
        default:
            spdlog::debug("unknown exception type, []", e);
            std::abort();
    }
}

#define _ZJ_THROW(error, ...) (_ZjThrow(error, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__))

// no need to chain messages anymore
#define _ZJ_TRY(function)                                                                                                                  \
    do {                                                                                                                                   \
        try {                                                                                                                              \
            function;                                                                                                                      \
        } catch (const ZjCritical& e) {                                                                                                    \
            _ZjThrow(ZjExceptionType::Critical, __FILE__, __LINE__, __FUNCTION__);                                                         \
        } catch (const ZjError& e) {                                                                                                       \
            _ZjThrow(ZjExceptionType::Error, __FILE__, __LINE__, __FUNCTION__);                                                            \
        }                                                                                                                                  \
    } while (0)

void myFunc1()
{
    spdlog::info("my func 1");
    _ZJ_THROW(ZjExceptionType::Critical, "nested test error source");
}

void myFunc2()
{
    spdlog::info("my func 2");
    _ZJ_TRY(myFunc1());
}

int myFunc3()
{
    _ZJ_TRY(myFunc2());
    return 1;
}

int main()
{
    int i;
    _ZJ_TRY(i = myFunc3());

    _ZJ_INFO("{}", i);

    _ZJ_THROW(ZjExceptionType::Error, "testing {}", 1);

    return 0;
}
