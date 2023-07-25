#include <gtest/gtest.h>
#include "ZjSwitch.hpp"

int globalVar = 10;

void testSwitchOff()
{
    ZjSwitch::getInstance().turnOff();
}

void testSwitchOn()
{
    ZjSwitch::getInstance().turnOn();
}

void testTurnOffRoutine()
{
    globalVar++;
}

void testTurnOffRoutine2()
{
    globalVar++;
}

TEST(TestZjSwitch, One)
{
    EXPECT_EQ(ZjSwitch::getInstance().on(), true);

    ZjSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);

    ZjSwitch::getInstance().addRoutine(&testTurnOffRoutine);
    ZjSwitch::getInstance().addRoutine(&testTurnOffRoutine2);
    EXPECT_EQ(ZjSwitch::getInstance().numRoutines(), 2);

    EXPECT_EQ(globalVar, 10);
    ZjSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 12);

    ZjSwitch::getInstance().removeRoutines();
    EXPECT_EQ(ZjSwitch::getInstance().numRoutines(), 0);

    testSwitchOn();
    EXPECT_EQ(ZjSwitch::getInstance().on(), true);
    testSwitchOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 12);
}