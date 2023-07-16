#include "ZjDebug.hpp"
#include "ZjLogMacros.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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
    //     _ZJ_THROW(ZjE::Fault, "wrong logic");
    // }

    _ZJ_THROW_IF(!f0(), "wrong logic here");

    _ZJ_MSG(ZjL::Info, "hello");
    _ZJ_MSG(ZjL::Trace, "here");

    // _ZJ_ASSERT(1);

    // if (i != 2) {
    //     _ZJ_THROW(ZjE::Fault, "wrong logic");
    // }

    _ZJ_THROW_IF(i != 2, "wrong index");
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

    spdlog::set_level(spdlog::level::trace);
    auto console = spdlog::stdout_color_mt("console");

    _ZJ_TRY(f3());

    return 0;
}