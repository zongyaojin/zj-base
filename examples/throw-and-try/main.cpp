#include "zj-debug.hpp"
#include "zj-logging-macros-simplified.hpp"

void F1(int i)
{
    spdlog::info("in F1");

    if (i == 2) {
        throw std::invalid_argument("throwing std exception");
    }

    _ZJ_THROW_IF(i != 2, "throwing ZjFault");
}

void F2(int i)
{
    spdlog::info("in F2");
    _ZJ_TRY(F1(i));
}

void F3(int i)
{
    spdlog::info("in F3");
    _ZJ_TRY(F2(i));
}

int main()
{
    try {
        _ZJ_TRY(F3(2));
    } catch (const std::exception& e) {
        spdlog::info("got F3(2) exception: {}", e.what());
    }

    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");
    _ZJ_DEBUG("");

    try {
        _ZJ_TRY(F3(1));
    } catch (const std::exception& e) {
        spdlog::info("got F3(1) exception: {}", e.what());
    }

    return 0;
}
