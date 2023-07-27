#include "ZjDebug.hpp"

void f1(int i)
{
    spdlog::info("in f1");

    if (i == 2) {
        throw std::invalid_argument("i == 2 causing throw std error");
    }

    _ZJ_THROW_IF(i != 2, "i != 2 causing throw ZjFault");
}

void f2(int i)
{
    spdlog::info("in f2");
    _ZJ_TRY(f1(i));
}

void f3(int i)
{
    spdlog::info("in f3");
    _ZJ_TRY(f2(i));
}

int main()
{
    try {
        _ZJ_TRY(f3(2));
    } catch (...) {
        spdlog::info("got f3(2) exception");
    }

    try {
        _ZJ_TRY(f3(1));
    } catch (...) {
        spdlog::info("got f3(1) exception");
    }

    return 0;
}