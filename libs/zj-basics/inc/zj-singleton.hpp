/**
 * @file zj-singleton.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

/**
 * @brief Singleton base class using CRTP
 *
 * @see https://stackoverflow.com/a/34519373/6291896
 * @see https://stackoverflow.com/a/43524389
 * @see https://stackoverflow.com/a/1008289
 * @see https://stackoverflow.com/a/12249115
 * @see https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-160
 *
 * @warning If the child class needs constructor arguments, then you SHOULD design another wrapper class with the class that requires
 * constructor arguments as a member variable. For example, you can have a `unique_ptr<ClassRequiresConstructorArgument>` member variable,
 * and an `Singleton::GetInstance().init(...)` function to deal with the initialization of ClassRequiresConstructorArgument.
 *
 * @warning If you apply variadic template arguments to the `GetInstance(...)` function, it's very confusing since only the input arguments
 * used by the first time `Singleton::GetInstance(real...)` is called are applied to constructor the instance. The following calls still
 * have to provide some dummy arguments such as `Singleton::GetInstance(any_dummy...)` to match the function signature, they these dummy
 * arguments could potentially be anything, and will not be used since the instance was already constructed. Yet calling
 * `Singleton::GetInstance(any_dummy...)` makes it very difficult to the reader to trace what are the real constructor arguments used by the
 * instance specially in a program with multiple threads.
 *
 * @warning To summarize, with an `Singleton::GetInstance().init(...)` function, the whole program can call it only once, and never use
 * it again; which make the initialization easy to trace. In the contrast, calling `Singleton::GetInstance(real_or_dummy...)` all over the
 * place isn't a good design.
 *
 * @see For example `ZjSingletonWithInit` in `tests/testZjSingleton.cpp`, also comments at https://stackoverflow.com/a/1051076
 */
template <typename ChildType>
class ZjSingleton
{
public:
    static ChildType& GetInstance()
    {
        static ChildType instance_;
        return instance_;
    }

    ZjSingleton(const ZjSingleton&) = delete;
    ZjSingleton(ZjSingleton&&) = delete;
    ZjSingleton& operator=(const ZjSingleton&) = delete;
    ZjSingleton& operator=(ZjSingleton&&) = delete;

protected:
    ZjSingleton() = default;
    virtual ~ZjSingleton() = default;
};
