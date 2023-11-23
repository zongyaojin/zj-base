#include "zj-debug.hpp"
#include "zj-logging-macros-simplified.hpp"

void f1(int i)
{
    spdlog::info("in f1");

    if (i == 2) {
        throw std::invalid_argument("throwing std exception");
    }

    _ZJ_THROW_IF(i != 2, "throwing ZjFault");
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
    } catch (const std::exception& e) {
        spdlog::info("got f3(2) exception: {}", e.what());
    }

    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");

    try {
        _ZJ_TRY(f3(1));
    } catch (const std::exception& e) {
        spdlog::info("got f3(1) exception: {}", e.what());
    }

    return 0;
}
