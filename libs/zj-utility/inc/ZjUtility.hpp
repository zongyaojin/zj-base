#pragma once

#include "ZjDebug.hpp"
#include "ZjLogMacrosExtension.hpp"
#include "ZjConcepts.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <string>

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

template <ZjRawPointer T>
void _DeleteRawPointer(T& ptr)
{
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}