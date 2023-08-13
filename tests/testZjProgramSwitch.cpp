#include "gtest/gtest.h"
#include "ZjProgramSwitch.hpp"

int globalVar = 10;

void testSwitchOff()
{
    ZjProgramSwitch::getInstance().turnOff();
}

void testSwitchOn()
{
    ZjProgramSwitch::getInstance().turnOn();
}

void testTurnOffRoutine()
{
    globalVar++;
}

void testTurnOffRoutine2()
{
    globalVar += 9;
}

TEST(TestZjProgramSwitch, One)
{
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), true);

    ZjProgramSwitch::getInstance().turnOn();
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), true);

    ZjProgramSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), false);

    ZjProgramSwitch::getInstance().registerTurnOffRoutine(&testTurnOffRoutine);
    ZjProgramSwitch::getInstance().registerTurnOffRoutine(&testTurnOffRoutine2);

    EXPECT_EQ(globalVar, 10);
    ZjProgramSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 20);

    testSwitchOn();
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), true);
    testSwitchOff();
    EXPECT_EQ(ZjProgramSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 20);
}
