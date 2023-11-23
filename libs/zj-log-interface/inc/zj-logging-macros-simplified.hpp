/**
 * @file zj-logging-macros-simplified.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 *
 * @brief Simplified logging macros for client code to use
 */

#pragma once

#include "zj-logging-macros.hpp"

/// Assertion interface for client code
#define _ZJ_ASSERT(condition, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if (!(condition)) {                                                                                                                \
            _ZjAssert(#condition, std::source_location::current(), ##__VA_ARGS__);                                                         \
        }                                                                                                                                  \
    } while (0)

/// @{ Message interfaces
#define _ZJ_TRACE(msg, ...) _ZJ_MSG(ZjL::kTrace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T(interval_sec, msg, ...) _ZJ_MSG_T(ZjL::kTrace, interval_sec, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::kTrace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T_IF(condition, interval_sec, msg, ...) _ZJ_MSG_IF(condition, ZjL::kTrace, interval_sec, msg, ##__VA_ARGS__)

#define _ZJ_DEBUG(msg, ...) _ZJ_MSG(ZjL::kDebug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T(interval_sec, msg, ...) _ZJ_MSG_T(ZjL::kDebug, interval_sec, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::kDebug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T_IF(condition, interval_sec, msg, ...) _ZJ_MSG_IF(condition, ZjL::kDebug, interval_sec, msg, ##__VA_ARGS__)

#define _ZJ_INFO(msg, ...) _ZJ_MSG(ZjL::kInfo, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T(interval_sec, msg, ...) _ZJ_MSG_T(ZjL::kInfo, interval_sec, msg, ##__VA_ARGS__)
#define _ZJ_INFO_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::kInfo, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T_IF(condition, interval_sec, msg, ...) _ZJ_MSG_IF(condition, ZjL::kInfo, interval_sec, msg, ##__VA_ARGS__)

#define _ZJ_WARN(msg, ...) _ZJ_MSG(ZjL::kWarn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T(interval_sec, msg, ...) _ZJ_MSG_T(ZjL::kWarn, interval_sec, msg, ##__VA_ARGS__)
#define _ZJ_WARN_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::kWarn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T_IF(condition, interval_sec, msg, ...) _ZJ_MSG_IF(condition, ZjL::kWarn, interval_sec, msg, ##__VA_ARGS__)
/// @}
