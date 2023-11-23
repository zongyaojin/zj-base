#include "gtest/gtest.h"
#include "zj-singleton.hpp"

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
    ZjSingletonTest::GetInstance().add(i);
}

TEST(TestZjSingleton, MultipleAccess)
{
    EXPECT_EQ(ZjSingletonTest::GetInstance().i(), 0);

    auto& instance = ZjSingletonTest::GetInstance();
    EXPECT_EQ(instance.i(), 0);

    ZjSingletonTest::GetInstance().add(10);
    EXPECT_EQ(ZjSingletonTest::GetInstance().i(), 10);
    EXPECT_EQ(instance.i(), 10);

    addToSingleton(3);
    EXPECT_EQ(ZjSingletonTest::GetInstance().i(), 13);
    EXPECT_EQ(instance.i(), 13);
}

// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------

class ZjSingletonWithInit : public ZjSingleton<ZjSingletonWithInit>
{
public:
    inline void Init(const int i)
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
    ZjSingletonWithInit::GetInstance().add(i);
}

TEST(TestZjSingletonWithInit, MultipleAccess)
{
    ZjSingletonWithInit::GetInstance().Init(1000);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().i(), 1000);

    auto& instance = ZjSingletonWithInit::GetInstance();
    EXPECT_EQ(instance.i(), 1000);

    ZjSingletonWithInit::GetInstance().add(10);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().i(), 1010);
    EXPECT_EQ(instance.i(), 1010);

    addToSingletonWithInit(3);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().i(), 1013);
    EXPECT_EQ(instance.i(), 1013);
}
