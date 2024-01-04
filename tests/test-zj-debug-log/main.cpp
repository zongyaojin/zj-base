#include "gtest/gtest.h"
#include "zj-logging.hpp"

#include <filesystem>

void TestZjThrowIf(const bool flag, const std::string& msg = "")
{
    if (msg.empty()) {
        _ZJ_THROW_IF(flag);
    } else {
        _ZJ_THROW_IF(flag, msg);
    }
}

void TestZjThrowFailureIf(const bool flag, const std::string& msg = "")
{
    if (msg.empty()) {
        _ZJ_THROW_FAILURE_IF(flag);
    } else {
        _ZJ_THROW_FAILURE_IF(flag, msg);
    }
}

inline void NoThrow() { _ZJ_INFO("not throwing anything"); }

void ThrowStdException() { throw std::runtime_error("bar"); }

void UpstreamFault() { TestZjThrowIf(true, "bar"); }

void UpstreamFailure() { TestZjThrowFailureIf(true, "bar"); }

void TestZjTry(const int type)
{
    if (type == 1) {
        _ZJ_TRY(NoThrow());
    } else if (type == 2) {
        _ZJ_TRY(ThrowStdException());
    } else if (type == 3) {
        _ZJ_TRY(TestZjThrowIf(true, "bar"));
    } else if (type == 4) {
        _ZJ_TRY(TestZjThrowFailureIf(true, "bar"));
    } else if (type == 5) {
        _ZJ_TRY(UpstreamFault());
    } else if (type == 6) {
        _ZJ_TRY(UpstreamFailure());
    }
}

int TestZjAssert(const bool flag, const std::string& msg = "")
{
    _ZJ_ASSERT(flag, msg);
    return 1;
}

int TestZjPrint(const bool flag, const std::string& msg = "")
{
    _ZJ_PRINT_IF(flag, msg);
    return 1;
}

TEST(TestZjThrow, ThrowExceptions)
{
    ZjLogger::GetInstance().Init(__ZJ_PKG_BUILD_PATH_NO_SLASH__, __ZJ_PKG_BUILD_PATH_NO_SLASH__);

    EXPECT_THROW(_ZJ_THROW(), ZjFault);
    EXPECT_THROW(_ZJ_THROW("foo"), ZjFault);

    EXPECT_THROW(_ZJ_THROW_FAILURE(), ZjFailure);
    EXPECT_THROW(_ZJ_THROW_FAILURE("foo"), ZjFailure);

    auto log_filename = ZjLogger::GetInstance().Filename();
    _ZJ_INFO("output log file: {}", log_filename);
    if (!log_filename.empty()) { EXPECT_TRUE(std::filesystem::exists(log_filename)); }
}

TEST(TestZjThrow, ThrowExceptionsIf)
{
    EXPECT_THROW(TestZjThrowIf(true), ZjFault);
    EXPECT_THROW(TestZjThrowIf(true, "foo"), ZjFault);

    EXPECT_NO_THROW(TestZjThrowIf(false));
    EXPECT_NO_THROW(TestZjThrowIf(false, "foo"));

    EXPECT_THROW(TestZjThrowFailureIf(true), ZjFailure);
    EXPECT_THROW(TestZjThrowFailureIf(true, "foo"), ZjFailure);

    try {
        TestZjThrowFailureIf(true, "foo");
    } catch (const std::exception& e) {
        std::cout << "\n\n\n" << e.what() << "\n\n\n" << std::endl;
    }

    EXPECT_NO_THROW(TestZjThrowFailureIf(false));
    EXPECT_NO_THROW(TestZjThrowFailureIf(false, "foo"));

    auto log_filename = ZjLogger::GetInstance().Filename();
    _ZJ_INFO("output log file: {}", log_filename);

    if (!log_filename.empty()) { EXPECT_TRUE(std::filesystem::exists(log_filename)); }
}

TEST(TestZjTry, TryCatchExceptions)
{
    EXPECT_NO_THROW(TestZjTry(1));
    EXPECT_THROW(TestZjTry(2), ZjBug);
    EXPECT_THROW(TestZjTry(3), ZjFault);
    EXPECT_THROW(TestZjTry(4), ZjFailure);
    EXPECT_THROW(TestZjTry(5), ZjFault);
    EXPECT_THROW(TestZjTry(6), ZjFailure);

    auto log_filename = ZjLogger::GetInstance().Filename();
    _ZJ_INFO("output log file: {}", log_filename);

    if (!log_filename.empty()) { EXPECT_TRUE(std::filesystem::exists(log_filename)); }
}

TEST(TestZjAssert, AssertCases)
{
    EXPECT_EQ(TestZjAssert(true), 1);
    EXPECT_EQ(TestZjAssert(true, "foo-bar"), 1);

    // https://stackoverflow.com/a/71257678
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";
    ASSERT_DEATH(TestZjAssert(false), "");
    ASSERT_DEATH(TestZjAssert(false, "asserted false"), "");
}

TEST(TestZjPrintIf, PrintCases)
{
    bool flag;

    flag = false;
    EXPECT_EQ(TestZjPrint(flag), 1);
    EXPECT_EQ(TestZjPrint(flag, "dummy"), 1);

    flag = true;
    EXPECT_EQ(TestZjPrint(flag), 1);
    EXPECT_EQ(TestZjPrint(flag, "printer message"), 1);
}
