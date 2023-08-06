#include "zj-base/zj-debug.hpp"
#include "zj-base/ZjChrono.hpp"
#include "zj-base/ZjCsvLog.hpp"

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
    ZjLog::getInstance().init(std::string {__EXAMPLE_PKG_BUILD_PATH__});

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

    Eigen::Vector2d v;
    v << 11, 22;

    Eigen::VectorXd v2;
    v2.resize(6);
    v2 << 3.14, 3.14, 3.14, 3.14, 3.14, 3.14;

    ZjCsvLog::getInstance().log("csv-example-1", v);
    ZjCsvLog::getInstance().log("csv-example-2", v2);

    ZjCsvLog::getInstance().log("csv-example-1", v);
    ZjCsvLog::getInstance().log("csv-example-2", v2);
    
    ZjCsvLog::getInstance().log("csv-example-1", v);
    ZjCsvLog::getInstance().log("csv-example-2", v2);
    ZjCsvLog::getInstance().log("csv-example-2", v2);

    return 0;
}