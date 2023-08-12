/**
 * @file ZjExceptions.hpp
 *
 * @brief Zj exceptions and exception types enum
 *
 * @author Zongyao Jin
 * @date 2023-07-26
 */

#pragma once

#include <cstdint>
#include <exception>
#include <string>

/// ZjException types enum
enum class ZjExceptionType : std::uint8_t
{
    Bug = 0,
    Fault,
    Failure,
};

/// ZjExceptionType short alias
using ZjE = ZjExceptionType;

/// ZjException base
class ZjException : public std::exception
{
protected:
    ZjException() = default;
    virtual ~ZjException() noexcept = default;

    ZjException(const std::string& msg)
    : m_msg(msg)
    {
    }

public:
    virtual const char* what() const noexcept { return m_msg.c_str(); }

protected:
    std::string m_msg {"see log trace for details"};
};

/// External level, reserved for catching and re-throwing external, non-zj exceptions
class ZjBug : public ZjException
{
public:
    ZjBug() = default;
    virtual ~ZjBug() noexcept = default;

    ZjBug(const std::string& msg)
    : ZjException(msg)
    {
    }
};

/// Fault level exception
class ZjFault : public ZjException
{
public:
    ZjFault() = default;
    virtual ~ZjFault() noexcept = default;

    ZjFault(const std::string& msg)
    : ZjException(msg)
    {
    }
};

/// Failure level exception
class ZjFailure : public ZjException
{
public:
    ZjFailure() = default;
    virtual ~ZjFailure() noexcept = default;

    ZjFailure(const std::string& msg)
    : ZjException(msg)
    {
    }
};
