#include "ZjTrial.hpp"

int main()
{
    // _ZjThrow(ZjEt::Bug, ZjFault("hmm"), std::source_location::current(), "haa?");
    _ZJ_THROW(true);
    return 0;
}