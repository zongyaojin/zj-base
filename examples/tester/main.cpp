#include "ZjThrow.hpp"

int main()
{
    _ZjThrow(ZjEt::Fault, ZjFault(), std::source_location::current());
    return 0;
}