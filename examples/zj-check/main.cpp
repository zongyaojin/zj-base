#include "ZjCheckNumerics.hpp"
#include "ZjLogMacroExtensions.hpp"

int main()
{
    double i = std::nan("1");

    Eigen::Vector3d v;
    v << 1, 2, i;
    ZjLog::getInstance().init(__ZJ_PKG_BUILD_PATH_NO_SLASH__, __ZJ_PKG_BUILD_PATH_NO_SLASH__);

    try {
        _ZJ_CHECK(i);
    } catch (...) {
    }

    try {
        _ZJ_CHECK(v);
    } catch (const std::exception& e) {
        _ZJ_INFO("get exception:\n{}", e.what());
    }

    return 0;
}
