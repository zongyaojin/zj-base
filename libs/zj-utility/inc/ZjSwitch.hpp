#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

class ZjSwitch : public ZjSingleton<ZjSwitch>
{
public:
    inline bool on() { return m_on; }

    void turnOn();

    void turnOff();

    void registerTurnOffRoutine(const std::function<void()>& routine);

private:
    bool m_on {false};
    
    std::vector<std::function<void()>> m_turnOffRoutine;
};