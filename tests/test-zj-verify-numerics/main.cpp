#include "gtest/gtest.h"
#include "zj-log.hpp"

Eigen::Vector3d invalidEigen()
{
    Eigen::Vector3d v;
    v << 1, 2, std::nan("1");
    return v;
}

double invalidDouble()
{
    return std::nan("1");
}

void foo(bool flag)
{
    if (flag) {
        _ZJ_VERIFY(invalidEigen());
    } else {
        _ZJ_VERIFY(invalidDouble());
    }
}

void bar(bool flag)
{
    _ZJ_TRY(foo(flag));
}

void hello(bool flag)
{
    _ZJ_TRY(bar(flag));
}

void world(bool flag)
{
    _ZJ_TRY(hello(flag));
}

void noThrow()
{
    invalidEigen();
    invalidDouble();
}

TEST(TestZjVerify, DirectVerify)
{
    double i = std::nan("1");
    Eigen::Vector3d v;
    v << 1, 2, i;
    Eigen::Matrix2d m;
    m << 1, 2, 3, i;
    EXPECT_THROW(_ZJ_VERIFY(i), ZjSingularity);
    EXPECT_THROW(_ZJ_VERIFY(v), ZjSingularity);
    EXPECT_THROW(_ZJ_VERIFY(m), ZjSingularity);
}

TEST(TestZjThrow, TraceVerify)
{
    EXPECT_THROW(_ZJ_TRY(world(true)), ZjSingularity);
    EXPECT_THROW(_ZJ_TRY(world(false)), ZjSingularity);

    _ZJ_DEBUG("");
    EXPECT_NO_THROW(_ZJ_TRY(noThrow()));
}

TEST(TestZjTry, NoSingular)
{
    double i = 3;
    Eigen::Vector3d v;
    v << 1, 2, 3;

    Eigen::Matrix2d m;
    m << 1, 2, 3, 4;

    EXPECT_NO_THROW(_ZJ_VERIFY(i));
    EXPECT_NO_THROW(_ZJ_VERIFY(v));
    EXPECT_NO_THROW(_ZJ_VERIFY(m));
}
