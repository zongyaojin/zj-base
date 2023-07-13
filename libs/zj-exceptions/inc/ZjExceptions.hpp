#pragma once

#include <cstdint>
#include <exception>
#include <string>

enum class ZjExceptionType : std::uint8_t
{
    Fault = 0,
    Failure,
};

using ZjEt = ZjExceptionType;

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
    std::string m_msg;
};

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