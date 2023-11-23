#include "gtest/gtest.h"
#include "zj-program-switch.hpp"

int globalVar = 10;

void TestSwitchOff()
{
    ZjProgramSwitch::GetInstance().TurnOff();
}

void TestSwitchOn()
{
    ZjProgramSwitch::GetInstance().TurnOn();
}

void TestTurnOffRoutine()
{
    globalVar++;
}

void TestTurnOffRoutine2()
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

    ZjProgramSwitch::GetInstance().RegisterTurnOffRoutine(&TestTurnOffRoutine);
    ZjProgramSwitch::GetInstance().RegisterTurnOffRoutine(&TestTurnOffRoutine2);

    EXPECT_EQ(globalVar, 10);
    ZjProgramSwitch::GetInstance().TurnOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), false);
    EXPECT_EQ(globalVar, 20);

    TestSwitchOn();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), true);
    TestSwitchOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().On(), false);
    EXPECT_EQ(globalVar, 20);
}
