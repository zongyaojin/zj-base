/**
 * @file zj-exceptions.hpp
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
    kBug = 0,
    kSingularity,
    kFault,
    kFailure,
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
    : msg_(msg)
    {
    }

public:
    virtual const char* what() const noexcept { return msg_.c_str(); }

protected:
    std::string msg_ {"refer to log trace top for more information"};
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
class ZjSingularity : public ZjException
{
public:
    ZjSingularity() = default;
    virtual ~ZjSingularity() noexcept = default;

    explicit ZjSingularity(const std::string& msg)
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
