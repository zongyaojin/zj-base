#include "ZjTimer.hpp"
#include <thread>

ZjTimer::ZjTimer(const std::string name)
{
    if (!name.empty()) {
        m_name = name;
    }
}


void ZjTimer::init(const unsigned frequency, const unsigned overtimeLimit)
{

}
