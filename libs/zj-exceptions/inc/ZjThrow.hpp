#include "ZjExceptions.hpp"
#include "ZjLog.hpp"
#include "ZjColors.hpp"

#include <source_location>
#include <fmt/format.h>

namespace zj {
namespace thrower {
static const std::string k_noPrint {"NO_PRINT_FOR_EXTERNAL_ERROR"};
}
}

template <typename... Args>
void _ZjThrow(
    const ZjEt t, const std::exception& e, const std::source_location& s, const std::string& fmt = "", Args&&... args)
{
    ZjLog::getInstance().info(fmt::format("{}:{}:{} @ " ZJ_I_WHITE "`{}`" ZJ_NO_COLOR, s.file_name(), s.line(), s.column(), s.function_name()));
    return;
}