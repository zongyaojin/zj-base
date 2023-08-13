/**
 * @file ZjUtility.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
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

/**
 * @brief Get key by value from an std::map or unordered_map
 *
 * @note This is just a convenient wrapper, in general, you should use:
 * ```cpp
 *      auto it = std::find_if(map.begin(), map.end(),
 *                  [value](const auto& map) -> bool {
 *                      return value == map.second;
 *                  });
 *      if (it != map.end()) {
 *          return it->first;
 *      } else {
 *          std::cout << "however you want to do" << std::endl;
 *      }
 * ```
 */
template <ZjMapType MapType, typename ValueType>
typename MapType::key_type _GetKeyByValue(const MapType& map, const ValueType& value)
{
    for (const auto& pair : map) {
        if (pair.second == value) { // cppcheck-suppress useStlAlgorithm
            return pair.first;
        }
    }

    _ZJ_THROW("no value found in map");
    return typename MapType::key_type {};
}

/// @brief Get enum (key) by string (value) from an unordered_map of enum and string
/// @see _GetKeyByValue for notes
template <ZjEnumType T>
T _GetEnumByString(const std::unordered_map<T, std::string>& map, const std::string& name)
{
    for (const auto& pair : map) {
        if (pair.second == name) { // cppcheck-suppress useStlAlgorithm
            return pair.first;
        }
    }

    _ZJ_THROW("no name [{}] found in map", name);
    return T {};
}

/// Delete raw pointer
template <ZjRawPointer T>
void _DeleteRawPointer(T* ptr)
{
    if (*ptr) {
        delete *ptr;
        *ptr = nullptr;
    }
}
