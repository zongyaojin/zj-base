#include "ZjTrial.hpp"

int main()
{
    // _ZjThrow(ZjEt::Bug, ZjFault("hmm"), std::source_location::current(), "haa?");
    _ZJ_THROW(ZjEt::Fault, "let's see");
    return 0;
}