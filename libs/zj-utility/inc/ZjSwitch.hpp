#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

class ZjSwitch : public ZjSingleton<ZjSwitch>
{
public:
    inline bool on() { return m_on; }

    inline void turnOn() { m_on = true; }

    void turnOff();

    void addRoutine(const std::function<void()>& routine);

    inline void removeRoutines() { m_routines.clear(); }
    
    inline auto numRoutines() { return m_routines.size(); }

private:
    bool m_on {true};
    std::vector<std::function<void()>> m_routines;
};