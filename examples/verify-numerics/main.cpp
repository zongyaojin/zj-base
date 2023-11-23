#include "zj-verify-numerics.hpp"
#include "zj-logging-macros-simplified.hpp"

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

int main()
{
    double i = std::nan("1");
    Eigen::Vector3d v;
    v << 1, 2, i;

    try {
        _ZJ_VERIFY(i);
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    try {
        _ZJ_VERIFY(v);
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");

    try {
        _ZJ_TRY(world(true));
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");

    try {
        world(false);
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    return 0;
}
