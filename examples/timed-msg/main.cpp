#include "ZjLogMacroExtensions.hpp"

int main()
{
    int i = 0;
    while (i++ < 1e7) {
        _ZJ_INFO_T(0.11, "hi");
        _ZJ_WARN_T(0.2, "hi");
        _ZJ_DEBUG_T(0.3, "hi");
        _ZJ_TRACE_T(0.22, "hi");
    }

    return 0;
}