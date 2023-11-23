#include "gtest/gtest.h"

#include "zj-utility.hpp"

#include <map>
#include <unordered_map>

const std::map<double, int> k_map {
    {1.1, 1},
    {2.2, 2},
};

const std::unordered_map<double, int> k_unorderedMap {
    {1.1, 1},
    {2.2, 2},
};

enum class TestType
{
    A = 0,
    B,
};

const std::map<TestType, std::string> k_enumStringMap {
    {TestType::A, "A"},
    {TestType::B, "B"},
};

const std::unordered_map<TestType, std::string> k_enumStringUnorderedMap {
    {TestType::A, "A"},
    {TestType::B, "B"},
};

TEST(TestMap, GeneralMaps)
{
    EXPECT_NEAR(ZjGetKeyByValue(k_map, 1), 1.1, std::numeric_limits<double>::min());
    EXPECT_NEAR(ZjGetKeyByValue(k_map, 2), 2.2, std::numeric_limits<double>::min());

    EXPECT_NEAR(ZjGetKeyByValue(k_unorderedMap, 1), 1.1, std::numeric_limits<double>::min());
    EXPECT_NEAR(ZjGetKeyByValue(k_unorderedMap, 2), 2.2, std::numeric_limits<double>::min());
}

TEST(TestMap, EnumStringMaps)
{
    EXPECT_EQ(ZjGetKeyByValue(k_enumStringMap, "A"), TestType::A);
    EXPECT_EQ(ZjGetKeyByValue(k_enumStringMap, "B"), TestType::B);

    EXPECT_EQ(ZjGetKeyByValue(k_enumStringUnorderedMap, "A"), TestType::A);
    EXPECT_EQ(ZjGetKeyByValue(k_enumStringUnorderedMap, "B"), TestType::B);
}

TEST(TestDeleteRawPointer, One)
{
    auto* i = new int {10};

    EXPECT_EQ(*i, 10);
    EXPECT_NE(i, nullptr);

    ZjDeleteRawPointer(&i);
    EXPECT_EQ(i, nullptr);
}
