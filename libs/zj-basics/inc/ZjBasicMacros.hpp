/**
 * @file ZjBasicMacros.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include <typeinfo>
#include <boost/core/demangle.hpp>
#include <boost/type_index.hpp>

/// Get a value's typename
#define _ZJ_DEMANGLE(value) (boost::core::demangle(typeid(value).name()))

/// Get a type's typename; removes const, volatile, & and && modifiers
#define _ZJ_TYPEID(type) (boost::typeindex::type_id<type>().pretty_name())

/// Get a type's typename; with const, volatile, & and && modifiers
#define _ZJ_TYPEID_RAW(type) (boost::typeindex::type_id_with_cvr<type>().pretty_name())

/// Check if a condition expression evaluates to boolean
#define _ZJ_STATIC_BOOLEAN_CHECK(condition)                                                                                                \
    do {                                                                                                                                   \
        using conditionType = std::remove_cvref_t<decltype(condition)>;                                                                    \
        constexpr bool boolType {std::is_same_v<conditionType, bool>};                                                                     \
        static_assert(boolType, "condition does not evaluate to boolean");                                                                 \
    } while (0)
