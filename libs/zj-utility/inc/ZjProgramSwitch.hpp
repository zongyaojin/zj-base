/**
 * @file ZjProgramSwitch.hpp
 *
 * @brief A global program switch
 *
 * @author Zongyao Jin
 * @date 2023-08-08
 */

#pragma once

#include "ZjSingleton.hpp"
#include "ZjDebug.hpp"

#include <vector>

/**
 * @brief A singleton class that's supposed to be used as the entire programs on off switch, you could register turn off routines in the
 * form of function pointers, and when the switch is turned off, all the routines will be executed as a final clean up
 *
 * @see tests/testZjProgramSwitch.cpp for an example
 */
class ZjProgramSwitch : public ZjSingleton<ZjProgramSwitch>
{
public:
    inline bool on() { return m_on; }

    inline void turnOn() { m_on = true; }

    /**
     * @brief Turn off the program switch, and before that, execute all registered functions
     * @warning Technically, you could register the same function twice, and it will executed twice; which is not recommended
     * @todo Figure out how to tell if a function was already registered, seems a little tricky; a function pointer doesn't have comparison
     * operators implemented, you cannot change the container to std::set<>, it won't compile; comparing two pointers directly also doesn't
     * seem work
     */
    void turnOff();

    /// Register functions to be executed before turning off
    void registerTurnOffRoutine(const std::function<void()>& routine);

private:
    bool m_on {true};

    std::vector<std::function<void()>> m_turnOffRoutine;
};