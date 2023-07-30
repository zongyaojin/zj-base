#include "ZjSwitch.hpp"
#include "ZjLogMacrosExtension.hpp"
#include "ZjLogsManager.hpp"

void ZjSwitch::turnOn()
{
    ZjLogsManager::getInstance().init();
    m_on = true;
}

void ZjSwitch::turnOff()
{
    if (!m_on) {
        return;
    }

    for (const auto& routine : m_turnOffRoutine) {
        if (routine) {
            routine();
        }
    }

    ZjLogsManager::getInstance().shutdown();
    m_turnOffRoutine.clear();
    m_on = false;
}

void ZjSwitch::registerTurnOffRoutine(const std::function<void()>& routine)
{
    if (!m_on) {
        turnOn();
    }

    if (!routine) {
        return;
    }

    m_turnOffRoutine.emplace_back(routine);
}