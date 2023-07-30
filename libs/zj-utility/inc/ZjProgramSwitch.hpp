#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

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