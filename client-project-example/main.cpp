#include "zj-base/zj-logging.hpp"
#include "zj-base/zj-utility.hpp"

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "spdlog/spdlog.h"

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
    ZjLogger::GetInstance().Init(std::string {__EXAMPLE_PKG_BUILD_PATH__}, std::string {__EXAMPLE_PKG_BUILD_PATH__});

    _ZJ_INFO("hello info");
    _ZJ_WARN("hello warn");
    _ZJ_DEBUG("hello debug");
    _ZJ_TRACE("hello trace");

    spdlog::critical("=======================================================================");
    spdlog::critical("Note that all external dependencies are ported to the client project");
    spdlog::critical("To change this, adjust settings in the CMake install function");
    spdlog::critical("Consider selecting PUBLIC, INTERFACE, or PRIVATE");
    spdlog::critical("=======================================================================");

    _ZJ_INFO("time iso: {}", ZjChrono::ZjGetTimeIso());

    try {
        bar();
    } catch (const std::exception& e) {
        _ZJ_DEBUG("got intentional exception [{}]", e.what());
    }

    Eigen::Vector2d v;
    v << 11, 22;

    Eigen::VectorXd v2;
    v2.resize(6);
    v2 << 3.14, 3.14, 3.14, 3.14, 3.14, 3.14;

    ZjCsvLogger::GetInstance().Log("csv-example-1", v);
    ZjCsvLogger::GetInstance().Log("csv-example-2", v2);

    ZjCsvLogger::GetInstance().Log("csv-example-1", v);
    ZjCsvLogger::GetInstance().Log("csv-example-2", v2);

    ZjCsvLogger::GetInstance().Log("csv-example-1", v);
    ZjCsvLogger::GetInstance().Log("csv-example-2", v2);
    ZjCsvLogger::GetInstance().Log("csv-example-2", v2);

    _ZJ_DEBUG("");
    _ZJ_INFO("===================================================");
    _ZJ_INFO("Successfully reached the end of the example program");
    _ZJ_INFO("===================================================");
    return 0;
}
