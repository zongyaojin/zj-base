#include "zj-verify-numerics.hpp"
#include "zj-logging-macros-simplified.hpp"

Eigen::Vector3d InvalidEigen()
{
    Eigen::Vector3d v;
    v << 1, 2, std::nan("1");
    return v;
}

double InvalidDouble()
{
    return std::nan("1");
}

void Foo(bool flag)
{
    if (flag) {
        _ZJ_VERIFY(InvalidEigen());
    } else {
        _ZJ_VERIFY(InvalidDouble());
    }
}

void Bar(bool flag)
{
    _ZJ_TRY(Foo(flag));
}

void Hello(bool flag)
{
    _ZJ_TRY(Bar(flag));
}

void World(bool flag)
{
    _ZJ_TRY(Hello(flag));
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
        _ZJ_TRY(World(true));
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");

    try {
        World(false);
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception: {}", e.what());
    }

    return 0;
}
