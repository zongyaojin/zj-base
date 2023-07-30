#include <gtest/gtest.h>
#include "zj-debug.hpp"

class ZjSingletonTest : public ZjSingleton<ZjSingletonTest>
{
public:
    inline void add(const int i) { m_i += i; }
    inline int i() const { return m_i; }

protected:
    int m_i {0};
};

/// @note the getInstance in this case is a little confusing since after the first time, you can pass any argument value, it doesn't matter,
/// because the static instance is already constructed; it won't construct again with the new value
class ZjSingletonCtrTest : public ZjSingleton<ZjSingletonCtrTest, int>
{
    friend class ZjSingleton<ZjSingletonCtrTest, int>;

public:
    inline int addToBase(const int a) { return m_base += a; }
    inline int base() const { return m_base; }

protected:
    ZjSingletonCtrTest(int base)
    : m_base(base) {};
    virtual ~ZjSingletonCtrTest() = default;

    int m_base {0};
};

void addToSingleton(const int i)
{
    ZjSingletonTest::getInstance().add(i);
}

void addToSingletonCtrTest(const int i)
{
    ZjSingletonCtrTest::getInstance(0).addToBase(i);
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

TEST(TestZjSingletonCtr, MultipleAccess)
{
    EXPECT_EQ(ZjSingletonCtrTest::getInstance(0).base(), 0);

    auto& instance1 = ZjSingletonCtrTest::getInstance(0);
    EXPECT_EQ(instance1.base(), 0);

    auto& instance10Actually1 = ZjSingletonCtrTest::getInstance(123);
    EXPECT_EQ(instance10Actually1.base(), 0);

    ZjSingletonCtrTest::getInstance(133).addToBase(10);
    EXPECT_EQ(ZjSingletonCtrTest::getInstance(-1).base(), 10);
    EXPECT_EQ(instance1.base(), 10);
    EXPECT_EQ(instance10Actually1.base(), 10);

    addToSingletonCtrTest(3);
    EXPECT_EQ(ZjSingletonCtrTest::getInstance(-30).base(), 13);
    EXPECT_EQ(instance1.base(), 13);
    EXPECT_EQ(instance10Actually1.base(), 13);
}