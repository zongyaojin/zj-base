/**
 * @file ZjUtility.hpp
 *
 * @brief Utility functions
 *
 * @author Zongyao Jin
 * @date 2023-08-08
 */

#pragma once

#include "ZjDebug.hpp"
#include "ZjLogMacroExtensions.hpp"
#include "ZjConcepts.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <string>

/// Get key by value from an std::map or unordered_map
template <ZjMapType MapType, typename ValueType>
typename MapType::key_type _GetKeyByValue(const MapType& map, const ValueType& value)
{
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first;
        }
    }

    _ZJ_THROW("no value found in map");
    return typename MapType::key_type {};
}

/// Get enum (key) by string (value) from an unordered_map of enum and string
template <ZjEnumType T>
T _GetEnumByString(const std::unordered_map<T, std::string>& map, const std::string& name)
{
    for (const auto& pair : map) {
        if (pair.second == name) {
            return pair.first;
        }
    }

    _ZJ_THROW("no name [{}] found in map", name);
    return T {};
}

/// Delete raw pointer
template <ZjRawPointer T>
void _DeleteRawPointer(T& ptr)
{
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}
