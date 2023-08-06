#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

/**
 * @brief A singleton that's supposed to be used as the entire programs on off switch, you could register turn off routines in the form of
 * function pointers, and when the switch is turned off, all the routines will be executed as a final clean up
 * @see tests/testZjProgramSwitch.cpp for an example
 */
class ZjProgramSwitch : public ZjSingleton<ZjProgramSwitch>
{
public:
    inline bool on() { return m_on; }

    inline void turnOn() { m_on = true; }

    void turnOff();

    void registerTurnOffRoutine(const std::function<void()>& routine);

private:
    bool m_on {true};

    std::vector<std::function<void()>> m_turnOffRoutine;
};