#include "gtest/gtest.h"
#include "zj-program-switch.hpp"

int globalVar = 10;

void testSwitchOff()
{
    ZjProgramSwitch::GetInstance().TurnOff();
}

void testSwitchOn()
{
    ZjProgramSwitch::GetInstance().TurnOn();
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
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), true);

    ZjProgramSwitch::GetInstance().TurnOn();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), true);

    ZjProgramSwitch::GetInstance().TurnOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), false);

    ZjProgramSwitch::GetInstance().RegisterTurnOffRoutine(&testTurnOffRoutine);
    ZjProgramSwitch::GetInstance().RegisterTurnOffRoutine(&testTurnOffRoutine2);

    EXPECT_EQ(globalVar, 10);
    ZjProgramSwitch::GetInstance().TurnOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), false);
    EXPECT_EQ(globalVar, 20);

    testSwitchOn();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), true);
    testSwitchOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), false);
    EXPECT_EQ(globalVar, 20);
}
