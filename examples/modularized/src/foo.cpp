#include "foo.hpp"
#include "zj-logging-macros-simplified.hpp"

void foo()
{
    Eigen::Vector2d v {3.14, 5.28};
    _ZJ_DEBUG("v: {}, {}", v(0), v(1));
}
