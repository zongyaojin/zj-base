#include <gtest/gtest.h>
#include "zj-debug.hpp"

void testZjThrowIf(const bool flag, const std::string& msg = "")
{
    if (msg.empty()) {
        _ZJ_THROW_IF(flag);
    } else {
        _ZJ_THROW_IF(flag, msg);
    }
}

void testZjThrowFailureIf(const bool flag, const std::string& msg = "")
{
    if (msg.empty()) {
        _ZJ_THROW_FAILURE_IF(flag);
    } else {
        _ZJ_THROW_FAILURE_IF(flag, msg);
    }
}

inline void noThrow()
{
    _ZJ_INFO("not throwing anything");
}

void throwStdException()
{
    throw std::runtime_error("bar");
}

void upstreamFault()
{
    testZjThrowIf(true, "bar");
}

void upstreamFailure()
{
    testZjThrowFailureIf(true, "bar");
}

void testZjTry(const int type)
{
    if (type == 1) {
        _ZJ_TRY(noThrow());
    } else if (type == 2) {
        _ZJ_TRY(throwStdException());
    } else if (type == 3) {
        _ZJ_TRY(testZjThrowIf(true, "bar"));
    } else if (type == 4) {
        _ZJ_TRY(testZjThrowFailureIf(true, "bar"));
    } else if (type == 5) {
        _ZJ_TRY(upstreamFault());
    } else if (type == 6) {
        _ZJ_TRY(upstreamFailure());
    }
}

int testZjAssert(const bool flag, const std::string& msg = "")
{
    _ZJ_ASSERT(flag, msg);
    return 1;
}

TEST(TestZjThrow, ThrowExceptions)
{
    EXPECT_THROW(_ZJ_THROW(), ZjFault);
    EXPECT_THROW(_ZJ_THROW("foo"), ZjFault);

    EXPECT_THROW(_ZJ_THROW_FAILURE(), ZjFailure);
    EXPECT_THROW(_ZJ_THROW_FAILURE("foo"), ZjFailure);
}

TEST(TestZjThrow, ThrowExceptionsIf)
{
    EXPECT_THROW(testZjThrowIf(true), ZjFault);
    EXPECT_THROW(testZjThrowIf(true, "foo"), ZjFault);

    EXPECT_NO_THROW(testZjThrowIf(false));
    EXPECT_NO_THROW(testZjThrowIf(false, "foo"));

    EXPECT_THROW(testZjThrowFailureIf(true), ZjFailure);
    EXPECT_THROW(testZjThrowFailureIf(true, "foo"), ZjFailure);

    EXPECT_NO_THROW(testZjThrowFailureIf(false));
    EXPECT_NO_THROW(testZjThrowFailureIf(false, "foo"));
}

TEST(TestZjTry, TryCatchExceptions)
{
    EXPECT_NO_THROW(testZjTry(1));
    EXPECT_THROW(testZjTry(2), ZjBug);
    EXPECT_THROW(testZjTry(3), ZjFault);
    EXPECT_THROW(testZjTry(4), ZjFailure);
    EXPECT_THROW(testZjTry(5), ZjFault);
    EXPECT_THROW(testZjTry(6), ZjFailure);
}

TEST(TestZjAssert, AssertCases)
{
    EXPECT_EQ(testZjAssert(true), 1);
    EXPECT_EQ(testZjAssert(true, "foo-bar"), 1);
    EXPECT_DEATH(testZjAssert(false), "");
    EXPECT_DEATH(testZjAssert(false, "asserted false"), "");
}