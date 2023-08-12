/**
 * @file ZjLogMacroExtensions.hpp
 *
 * @brief Simplified log macro interfaces for client code to use
 *
 * @author Zongyao Jin
 * @date 2023-08-08
 */

#pragma once

#include "ZjLogMacros.hpp"

/// Assertion interface for client code
#define _ZJ_ASSERT(condition, ...)                                                                                                         \
    do {                                                                                                                                   \
        _ZJ_STATIC_BOOLEAN_CHECK(condition);                                                                                               \
        if (!(condition)) {                                                                                                                \
            _ZjAssert(#condition, std::source_location::current(), ##__VA_ARGS__);                                                         \
        }                                                                                                                                  \
    } while (0)

/// @{ Message interfaces
#define _ZJ_TRACE(msg, ...) _ZJ_MSG(ZjL::Trace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T(intervalSec, msg, ...) _ZJ_MSG_T(ZjL::Trace, intervalSec, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Trace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T_IF(condition, intervalSec, msg, ...) _ZJ_MSG_IF(condition, ZjL::Trace, intervalSec, msg, ##__VA_ARGS__)

#define _ZJ_DEBUG(msg, ...) _ZJ_MSG(ZjL::Debug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T(intervalSec, msg, ...) _ZJ_MSG_T(ZjL::Debug, intervalSec, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Debug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T_IF(condition, intervalSec, msg, ...) _ZJ_MSG_IF(condition, ZjL::Debug, intervalSec, msg, ##__VA_ARGS__)

#define _ZJ_INFO(msg, ...) _ZJ_MSG(ZjL::Info, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T(intervalSec, msg, ...) _ZJ_MSG_T(ZjL::Info, intervalSec, msg, ##__VA_ARGS__)
#define _ZJ_INFO_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Info, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T_IF(condition, intervalSec, msg, ...) _ZJ_MSG_IF(condition, ZjL::Info, intervalSec, msg, ##__VA_ARGS__)

#define _ZJ_WARN(msg, ...) _ZJ_MSG(ZjL::Warn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T(intervalSec, msg, ...) _ZJ_MSG_T(ZjL::Warn, intervalSec, msg, ##__VA_ARGS__)
#define _ZJ_WARN_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Warn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T_IF(condition, intervalSec, msg, ...) _ZJ_MSG_IF(condition, ZjL::Warn, intervalSec, msg, ##__VA_ARGS__)
/// @}
