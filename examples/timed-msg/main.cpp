#include "zj-debug.hpp"

int main()
{
    
    while (1) {
        _ZJ_INFO_T(0.5, "hi");
        _ZJ_WARN_T(1.5, "hi");
        _ZJ_DEBUG_T(3, "hi");
        _ZJ_TRACE_T(1, "hi");
    }

    return 0;
}