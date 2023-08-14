/**
 * @file ZjConcepts.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @brief Some concepts for templates
 */

#pragma once

#include <concepts>
#include <map>
#include <unordered_map>
#include <chrono>

#include "Eigen/Dense"

// Concept for enums
template <typename T>
concept ZjEnumType = std::is_enum_v<T>;

// Concept for std::map or std::unordered_map
template <typename T>
concept ZjMapType = std::is_same_v<T, std::map<typename T::key_type, typename T::mapped_type>> || std::is_same_v<T,
    std::unordered_map<typename T::key_type, typename T::mapped_type>>;

// Concept for second and sub-second std::chrono::durations
template <typename T>
concept ZjDuration = std::is_same_v<T, std::chrono::nanoseconds> || std::is_same_v<T, std::chrono::microseconds> || std::is_same_v<T,
    std::chrono::milliseconds> || std::is_same_v<T, std::chrono::seconds>;

/// Concept for pointers
template <typename T>
concept ZjRawPointer = std::is_pointer_v<T>;

/// Concept for arithmetics
template <typename T>
concept ZjArithmetic = std::is_arithmetic_v<T>;

/// Concept for Eigen matrix dimensionality constraint
template <decltype(Eigen::Dynamic) N>
concept ZjEigenSizeValid = (N != 0) && (N > -2);
