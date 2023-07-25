#include "ZjSwitch.hpp"
#include "ZjLogMacrosExtension.hpp"

void ZjSwitch::turnOff()
{
    for (const auto& routine : m_routines) {
        if (routine) {
            routine();
        }
    }

    m_on = false;
}

void ZjSwitch::addRoutine(const std::function<void()>& routine)
{
    if (!routine) {
        return;
    }

    m_routines.emplace_back(routine);
}