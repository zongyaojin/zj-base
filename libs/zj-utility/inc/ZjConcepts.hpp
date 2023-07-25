#pragma once

#include <concepts>
#include <map>
#include <unordered_map>

// Concept to check if a type is an enumeration
template <typename T>
concept ZjEnumType = std::is_enum_v<T>;

// Concept to check if a type is either std::map or std::unordered_map
template <typename T>
concept ZjMapType = std::is_same_v<T, std::map<typename T::key_type, typename T::mapped_type>> || std::is_same_v<T,
    std::unordered_map<typename T::key_type, typename T::mapped_type>>;

// Concept to check if a type is std::chrono::duration type
template <typename T>
concept ZjDuration = std::is_same_v<T, std::chrono::nanoseconds> || std::is_same_v<T, std::chrono::microseconds> || std::is_same_v<T,
    std::chrono::milliseconds> || std::is_same_v<T, std::chrono::seconds>;

template <typename T>
concept ZjRawPointer = std::is_pointer_v<T>;