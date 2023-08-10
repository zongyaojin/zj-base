#include "ZjLogMacroExtensions.hpp"

int main()
{
    _ZJ_INFO("pkg name: {}", __ZJ_PKG_NAME__);
    _ZJ_INFO("pkg source path: {}", __ZJ_PKG_SOURCE_PATH_NO_SLASH__);
    _ZJ_INFO("pkg build path: {}", __ZJ_PKG_BUILD_PATH_NO_SLASH__);
    _ZJ_INFO("pkg install bin path: {}", __ZJ_PKG_INSTALL_BIN_PATH_NO_SLASH__);

    _ZJ_INFO("pkg git branch: {}", __ZJ_PKG_GIT_BRANCH__);
    _ZJ_INFO("pkg git commit hash: {}", __ZJ_PKG_GIT_COMMIT_HASH__);
    _ZJ_INFO("pkg git commit time: {}", __ZJ_PKG_GIT_COMMIT_TIME__);
    _ZJ_INFO("pkg git tag: {}", __ZJ_PKG_GIT_TAG__);
    _ZJ_INFO("pkg git cmake cache time: {}", __ZJ_PKG_GIT_CMAKE_CACHE_TIME__);

    return 0;
}