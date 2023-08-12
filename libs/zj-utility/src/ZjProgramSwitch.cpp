#include "ZjProgramSwitch.hpp"

void ZjProgramSwitch::turnOff()
{
    if (!m_on) {
        return;
    }

    for (const auto& routine : m_turnOffRoutine) {
        if (routine) {
            routine();
        }
    }

    m_turnOffRoutine.clear();
    m_on = false;
}

void ZjProgramSwitch::registerTurnOffRoutine(const std::function<void()>& routine)
{
    if (!m_on) {
        turnOn();
    }

    if (!routine) {
        return;
    }

    m_turnOffRoutine.emplace_back(routine);
}
