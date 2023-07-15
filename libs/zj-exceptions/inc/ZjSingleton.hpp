/**
 * @file ZjSingleton.hpp
 * @brief Singleton base class using CRTP
 *
 * @see https://stackoverflow.com/a/34519373/6291896
 * @see https://stackoverflow.com/a/43524389
 * @see https://stackoverflow.com/a/1008289
 * @see https://stackoverflow.com/a/12249115
 * @see https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-160
 *
 * @author Zongyao Jin
 * @date 2023-7
 */

#pragma once

template <typename T>
class ZjSingleton
{
public:
    static T& getInstance()
    {
        static T s_instance;
        return s_instance;
    }

    ZjSingleton(const ZjSingleton&) = delete;
    ZjSingleton(ZjSingleton&&) = delete;
    ZjSingleton& operator=(const ZjSingleton&) = delete;
    ZjSingleton& operator=(ZjSingleton&&) = delete;

protected:
    ZjSingleton() = default;
    virtual ~ZjSingleton() = default;
};