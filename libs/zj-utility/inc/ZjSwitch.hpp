#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

class ZjSwitch : public ZjSingleton<ZjSwitch>
{
public:
    inline bool on() { return m_on; }

    inline void turnOn() { m_on = true; }

    void turnOff()
    {
        for (const auto& routine : turnOffRoutine) {
            if (routine) {
                routine();
            }
        }

        m_on = false;
    }

    void addTearDownRoutine(const std::function<void()> routine)
    {
        _ZJ_THROW_IF(!routine, "invalid function pointer");
        turnOffRoutine.push_back(routine);
    }

private:
    bool m_on {true};

    std::vector<std::function<void()>> turnOffRoutine;
};