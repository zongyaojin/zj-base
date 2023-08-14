/**
 * @file ZjExceptions.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include <string>
#include <exception>
#include <source_location>
#include <cstdint>

/// ZjException types enum
enum class ZjExceptionType : std::uint8_t
{
    Bug = 0,
    Singular,
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

    explicit ZjException(const std::string& msg)
    : m_msg(msg)
    {
    }

public:
    virtual const char* what() const noexcept { return m_msg.c_str(); }

protected:
    std::string m_msg {"refer to log trace top for more information"};
};

/// External level, reserved for catching and re-throwing external, non-zj exceptions
class ZjBug : public ZjException
{
public:
    ZjBug() = default;
    virtual ~ZjBug() noexcept = default;

    explicit ZjBug(const std::string& msg)
    : ZjException(msg)
    {
    }
};

/// Numerical singular level exception
class ZjSingular : public ZjException
{
public:
    ZjSingular() = default;
    virtual ~ZjSingular() noexcept = default;

    explicit ZjSingular(const std::string& msg)
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

    explicit ZjFault(const std::string& msg)
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

    explicit ZjFailure(const std::string& msg)
    : ZjException(msg)
    {
    }
};
