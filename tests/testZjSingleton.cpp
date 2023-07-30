#include <gtest/gtest.h>
#include "zj-debug.hpp"

#include <memory>
#include <stdexcept>

class ZjSingletonTest : public ZjSingleton<ZjSingletonTest>
{
public:
    inline void add(const int i) { m_i += i; }
    inline int i() const { return m_i; }

private:
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

// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------

class ZjSingletonWithInit : public ZjSingleton<ZjSingletonWithInit>
{
public:
    inline void init(const int i)
    {
        if (!m_i) {
            m_i = std::make_unique<int>(i);
        }
    }

    inline void add(const int i)
    {
        if (!m_i) {
            throw std::runtime_error {"not initialized"};
        }

        *m_i += i;
    }

    inline int i() const
    {
        if (!m_i) {
            throw std::runtime_error {"not initialized"};
        }

        return *m_i;
    }

private:
    std::unique_ptr<int> m_i;
};

void addToSingletonWithInit(const int i)
{
    ZjSingletonWithInit::getInstance().add(i);
}

TEST(TestZjSingletonWithInit, MultipleAccess)
{
    ZjSingletonWithInit::getInstance().init(1000);
    EXPECT_EQ(ZjSingletonWithInit::getInstance().i(), 1000);

    auto& instance = ZjSingletonWithInit::getInstance();
    EXPECT_EQ(instance.i(), 1000);

    ZjSingletonWithInit::getInstance().add(10);
    EXPECT_EQ(ZjSingletonWithInit::getInstance().i(), 1010);
    EXPECT_EQ(instance.i(), 1010);

    addToSingletonWithInit(3);
    EXPECT_EQ(ZjSingletonWithInit::getInstance().i(), 1013);
    EXPECT_EQ(instance.i(), 1013);
}
