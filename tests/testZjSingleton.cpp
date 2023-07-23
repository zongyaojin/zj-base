#include <gtest/gtest.h>
#include "zj-debug.hpp"

class ZjSingletonTest : public ZjSingleton<ZjSingletonTest>
{
public:
    void add(const int i) { m_i += i; }

    inline int i() const { return m_i; }

protected:
    int m_i {0};
};

void addToSingleton(const int i)
{
    ZjSingletonTest::getInstance().add(i);
}

TEST(TestZjSingleton, MultipleAccess)
{
    EXPECT_EQ(ZjSingletonTest::getInstance().i(), 0);

    auto& instance = ZjSingletonTest::getInstance();
    EXPECT_EQ(instance.i(), 0);

    ZjSingletonTest::getInstance().add(10);
    EXPECT_EQ(ZjSingletonTest::getInstance().i(), 10);
    EXPECT_EQ(instance.i(), 10);

    addToSingleton(3);
    EXPECT_EQ(ZjSingletonTest::getInstance().i(), 13);
    EXPECT_EQ(instance.i(), 13);
}