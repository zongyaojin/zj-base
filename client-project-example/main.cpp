#include "zj-base/zj-debug.hpp"
#include "zj-base/ZjChrono.hpp"

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <spdlog/spdlog.h>

void foo()
{
    _ZJ_DEBUG("\n\nin foo\n\n");
    _ZJ_THROW("intentional fault");
}

void bar()
{
    _ZJ_DEBUG("\n\nin bar\n\n");
    _ZJ_TRY(foo());
}

int main()
{

    _ZJ_INFO("hello info");
    _ZJ_WARN("hello warn");
    _ZJ_DEBUG("hello debug");
    _ZJ_TRACE("hello trace");

    _ZJ_INFO("time iso: {}", ZjChrono::getTimeIso());

    try {
        bar();
    } catch (const std::exception& e) {
        _ZJ_DEBUG("got intentional exception [{}]", e.what());
    }

    return 0;
}