#include "ZjTrial.hpp"
#include "spdlog/spdlog.h"

bool f0()
{
    return true;
}

void f1(int i)
{
    spdlog::info("f1");
    try {
        throw std::invalid_argument("err msg");
    } catch (...) {
        spdlog::info("got exception but ignored");
    }

    // if (i != 2) {
    //     _ZJ_THROW(ZjEt::Fault, "wrong logic");
    // }

    _ZJ_THROW_IF(!f0(), "wrong logic here");

    // _ZJ_ASSERT(1);
}

void f2()
{
    spdlog::info("f2");
    _ZJ_TRY(f1(1));
}

void f3()
{
    spdlog::info("f3");
    _ZJ_TRY(f2());
}

int main()
{
    _ZJ_TRY(f3());

    return 0;
}