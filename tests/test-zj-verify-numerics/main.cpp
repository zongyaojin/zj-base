#include "gtest/gtest.h"
#include "zj-logging.hpp"

Eigen::Vector3d InvalidEigen()
{
    Eigen::Vector3d v;
    v << 1, 2, std::nan("1");
    return v;
}

double InvalidDouble() { return std::nan("1"); }

void Foo(bool flag)
{
    if (flag) {
        _ZJ_VERIFY(InvalidEigen());
    } else {
        _ZJ_VERIFY(InvalidDouble());
    }
}

void Bar(bool flag) { _ZJ_TRY(Foo(flag)); }

void Hello(bool flag) { _ZJ_TRY(Bar(flag)); }

void World(bool flag) { _ZJ_TRY(Hello(flag)); }

void NoThrow()
{
    InvalidEigen();
    InvalidDouble();
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
    EXPECT_THROW(_ZJ_TRY(World(true)), ZjSingularity);
    EXPECT_THROW(_ZJ_TRY(World(false)), ZjSingularity);

    _ZJ_DEBUG("");
    EXPECT_NO_THROW(_ZJ_TRY(NoThrow()));
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
