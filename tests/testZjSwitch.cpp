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
    globalVar += 9;
}

TEST(TestZjSwitch, One)
{
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);

    ZjSwitch::getInstance().turnOn();
    EXPECT_EQ(ZjSwitch::getInstance().on(), true);

    ZjSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);

    ZjSwitch::getInstance().registerTurnOffRoutine(&testTurnOffRoutine);
    ZjSwitch::getInstance().registerTurnOffRoutine(&testTurnOffRoutine2);

    EXPECT_EQ(globalVar, 10);
    ZjSwitch::getInstance().turnOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 20);

    testSwitchOn();
    EXPECT_EQ(ZjSwitch::getInstance().on(), true);
    testSwitchOff();
    EXPECT_EQ(ZjSwitch::getInstance().on(), false);
    EXPECT_EQ(globalVar, 20);
}