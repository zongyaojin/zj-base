#include "gtest/gtest.h"
#include "ZjProgramSwitch.hpp"

int globalVar = 10;

void testSwitchOff()
{
    ZjProgramSwitch::GetInstance().turnOff();
}

void testSwitchOn()
{
    ZjProgramSwitch::GetInstance().turnOn();
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
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), true);

    ZjProgramSwitch::GetInstance().turnOn();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), true);

    ZjProgramSwitch::GetInstance().turnOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), false);

    ZjProgramSwitch::GetInstance().registerTurnOffRoutine(&testTurnOffRoutine);
    ZjProgramSwitch::GetInstance().registerTurnOffRoutine(&testTurnOffRoutine2);

    EXPECT_EQ(globalVar, 10);
    ZjProgramSwitch::GetInstance().turnOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), false);
    EXPECT_EQ(globalVar, 20);

    testSwitchOn();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), true);
    testSwitchOff();
    EXPECT_EQ(ZjProgramSwitch::GetInstance().on(), false);
    EXPECT_EQ(globalVar, 20);
}
