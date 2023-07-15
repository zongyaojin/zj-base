#pragma once


#include "ZjColors.hpp"

/// @brief A highlighted `static_assert` wrapper, somehow `static_assert` cannot be wrapped by `()` or `do-while(0)`
#define _ZJ_STATIC_ASSERT(condition, msg) static_assert(condition, ZJ_G_WHITE ZJ_BI_RED msg ZJ_NO_COLOR)


