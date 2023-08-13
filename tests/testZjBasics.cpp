#include "gtest/gtest.h"
#include "zj-utility.hpp"

int testStaticBoolCheckValid()
{
    _ZJ_STATIC_BOOLEAN_CHECK(true);
    _ZJ_STATIC_BOOLEAN_CHECK(false);

    int i = 10;
    _ZJ_STATIC_BOOLEAN_CHECK(i == 1);
    _ZJ_STATIC_BOOLEAN_CHECK(i == 10);

    return 1;
}

template <typename T>
std::string testZjDemangle(T input)
{
    return _ZJ_DEMANGLE(input);
}

TEST(TestZjStaticBooleanCheck, ValidCases)
{
    EXPECT_EQ(testStaticBoolCheckValid(), 1);
}

TEST(TestZjTypeTraits, Demangle)
{
    int i {0};
    double j {1.2};
    float k {2.3};
    ZjFault zjFault;
    ZjFailure zjFailure;

    EXPECT_EQ(testZjDemangle(i), "int");
    EXPECT_EQ(testZjDemangle(j), "double");
    EXPECT_EQ(testZjDemangle(k), "float");
    EXPECT_EQ(testZjDemangle(zjFault), "ZjFault");
    EXPECT_EQ(testZjDemangle(zjFailure), "ZjFailure");
}

TEST(TestZjTypeTraits, TypeId)
{
    EXPECT_EQ(_ZJ_TYPEID(int), "int");
    EXPECT_EQ(_ZJ_TYPEID(double), "double");
    EXPECT_EQ(_ZJ_TYPEID(float), "float");
    EXPECT_EQ(_ZJ_TYPEID(ZjFault), "ZjFault");
    EXPECT_EQ(_ZJ_TYPEID(ZjFailure), "ZjFailure");

    EXPECT_EQ(_ZJ_TYPEID(int*), "int*");
    EXPECT_EQ(_ZJ_TYPEID(double*), "double*");
    EXPECT_EQ(_ZJ_TYPEID(float*), "float*");
    EXPECT_EQ(_ZJ_TYPEID(ZjFault*), "ZjFault*");
    EXPECT_EQ(_ZJ_TYPEID(ZjFailure*), "ZjFailure*");

    // https://stackoverflow.com/a/1143272
    {
        EXPECT_EQ(_ZJ_TYPEID(const int* const), "int const*");
        EXPECT_EQ(_ZJ_TYPEID(const double* const), "double const*");
        EXPECT_EQ(_ZJ_TYPEID(const float* const), "float const*");
        EXPECT_EQ(_ZJ_TYPEID(const ZjFault* const), "ZjFault const*");
        EXPECT_EQ(_ZJ_TYPEID(const ZjFailure* const), "ZjFailure const*");

        EXPECT_EQ(_ZJ_TYPEID(const int*), "int const*");
        EXPECT_EQ(_ZJ_TYPEID(const double*), "double const*");
        EXPECT_EQ(_ZJ_TYPEID(const float*), "float const*");
        EXPECT_EQ(_ZJ_TYPEID(const ZjFault*), "ZjFault const*");
        EXPECT_EQ(_ZJ_TYPEID(const ZjFailure*), "ZjFailure const*");

        EXPECT_EQ(_ZJ_TYPEID(int* const), "int*");
        EXPECT_EQ(_ZJ_TYPEID(double* const), "double*");
        EXPECT_EQ(_ZJ_TYPEID(float* const), "float*");
        EXPECT_EQ(_ZJ_TYPEID(ZjFault* const), "ZjFault*");
        EXPECT_EQ(_ZJ_TYPEID(ZjFailure* const), "ZjFailure*");
    }

    EXPECT_EQ(_ZJ_TYPEID(const int&), "int");
    EXPECT_EQ(_ZJ_TYPEID(const double&), "double");
    EXPECT_EQ(_ZJ_TYPEID(const float&), "float");
    EXPECT_EQ(_ZJ_TYPEID(const ZjFault&), "ZjFault");
    EXPECT_EQ(_ZJ_TYPEID(const ZjFailure&), "ZjFailure");
}

TEST(TestZjTypeTraits, TypeIdRaw)
{
    EXPECT_EQ(_ZJ_TYPEID_RAW(int), "int");
    EXPECT_EQ(_ZJ_TYPEID_RAW(double), "double");
    EXPECT_EQ(_ZJ_TYPEID_RAW(float), "float");
    EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFault), "ZjFault");
    EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFailure), "ZjFailure");

    EXPECT_EQ(_ZJ_TYPEID_RAW(int*), "int*");
    EXPECT_EQ(_ZJ_TYPEID_RAW(double*), "double*");
    EXPECT_EQ(_ZJ_TYPEID_RAW(float*), "float*");
    EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFault*), "ZjFault*");
    EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFailure*), "ZjFailure*");

    // https://stackoverflow.com/a/1143272
    {
        EXPECT_EQ(_ZJ_TYPEID_RAW(const int* const), "int const* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const double* const), "double const* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const float* const), "float const* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFault* const), "ZjFault const* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFailure* const), "ZjFailure const* const");

        EXPECT_EQ(_ZJ_TYPEID_RAW(const int*), "int const*");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const double*), "double const*");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const float*), "float const*");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFault*), "ZjFault const*");
        EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFailure*), "ZjFailure const*");

        EXPECT_EQ(_ZJ_TYPEID_RAW(int* const), "int* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(double* const), "double* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(float* const), "float* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFault* const), "ZjFault* const");
        EXPECT_EQ(_ZJ_TYPEID_RAW(ZjFailure* const), "ZjFailure* const");
    }

    EXPECT_EQ(_ZJ_TYPEID_RAW(const int&), "int const&");
    EXPECT_EQ(_ZJ_TYPEID_RAW(const double&), "double const&");
    EXPECT_EQ(_ZJ_TYPEID_RAW(const float&), "float const&");
    EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFault&), "ZjFault const&");
    EXPECT_EQ(_ZJ_TYPEID_RAW(const ZjFailure&), "ZjFailure const&");
}
