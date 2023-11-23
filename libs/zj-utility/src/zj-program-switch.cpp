/**
 * @file zj-program-switch.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "zj-program-switch.hpp"

void ZjProgramSwitch::TurnOff()
{
    if (!on_) {
        return;
    }

    for (const auto& routine : turn_off_routines_) {
        if (routine) {
            routine();
        }
    }

    turn_off_routines_.clear();
    on_ = false;
}

void ZjProgramSwitch::RegisterTurnOffRoutine(const std::function<void()>& routine)
{
    if (!on_) {
        TurnOn();
    }

    if (!routine) {
        return;
    }

    turn_off_routines_.emplace_back(routine);
}
