/**
 * @file ZjProgramSwitch.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

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
