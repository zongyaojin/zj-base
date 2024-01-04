#include "gtest/gtest.h"
#include "zj-singleton.hpp"

#include <memory>
#include <stdexcept>

class ZjSingletonTest : public ZjSingleton<ZjSingletonTest>
{
public:
    inline void Add(const int i) { i_ += i; }
    inline int GetI() const { return i_; }

private:
    int i_ {0};
};

void addToSingleton(const int i) { ZjSingletonTest::GetInstance().Add(i); }

TEST(TestZjSingleton, MultipleAccess)
{
    EXPECT_EQ(ZjSingletonTest::GetInstance().GetI(), 0);

    auto& instance = ZjSingletonTest::GetInstance();
    EXPECT_EQ(instance.GetI(), 0);

    ZjSingletonTest::GetInstance().Add(10);
    EXPECT_EQ(ZjSingletonTest::GetInstance().GetI(), 10);
    EXPECT_EQ(instance.GetI(), 10);

    addToSingleton(3);
    EXPECT_EQ(ZjSingletonTest::GetInstance().GetI(), 13);
    EXPECT_EQ(instance.GetI(), 13);
}

// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------

class ZjSingletonWithInit : public ZjSingleton<ZjSingletonWithInit>
{
public:
    inline void Init(const int i)
    {
        if (!i_) { i_ = std::make_unique<int>(i); }
    }

    inline void Add(const int i)
    {
        if (!i_) { throw std::runtime_error {"not initialized"}; }

        *i_ += i;
    }

    inline int GetI() const
    {
        if (!i_) { throw std::runtime_error {"not initialized"}; }

        return *i_;
    }

private:
    std::unique_ptr<int> i_;
};

void addToSingletonWithInit(const int i) { ZjSingletonWithInit::GetInstance().Add(i); }

TEST(TestZjSingletonWithInit, MultipleAccess)
{
    ZjSingletonWithInit::GetInstance().Init(1000);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().GetI(), 1000);

    auto& instance = ZjSingletonWithInit::GetInstance();
    EXPECT_EQ(instance.GetI(), 1000);

    ZjSingletonWithInit::GetInstance().Add(10);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().GetI(), 1010);
    EXPECT_EQ(instance.GetI(), 1010);

    addToSingletonWithInit(3);
    EXPECT_EQ(ZjSingletonWithInit::GetInstance().GetI(), 1013);
    EXPECT_EQ(instance.GetI(), 1013);
}
