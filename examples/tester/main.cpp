#include "ZjTrial.hpp"

int main()
{
    // _ZjThrow(ZjEt::Bug, ZjFault("hmm"), std::source_location::current(), "haa?");
    _ZJ_THROW(ZjEt::Fault);
    return 0;
}