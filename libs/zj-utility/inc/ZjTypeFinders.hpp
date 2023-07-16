#pragma once

#include <typeinfo>
#include <boost/core/demangle.hpp>
#include <boost/type_index.hpp>

/// Gets a value's typename
#define _ZJ_DEMANGLE(value) (boost::core::demangle(typeid(value).name()))

/// Gets a type's typename; removes const, volatile, & and && modifiers
#define _ZJ_TYPEID(type) (boost::typeindex::type_id<type>().pretty_name())

/// Gets a type's typename; with const, volatile, & and && modifiers
#define _ZJ_TYPEID_RAW(type) (boost::typeindex::type_id_with_cvr<type>().pretty_name())
