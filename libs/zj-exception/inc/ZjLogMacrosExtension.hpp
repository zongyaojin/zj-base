#pragma once

#include "ZjLogMacros.hpp"

#define _ZJ_TRACE(msg, ...) _ZJ_MSG(ZjL::Trace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T(intervalS, msg, ...) _ZJ_MSG_T(ZjL::Trace, intervalS, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Trace, msg, ##__VA_ARGS__)
#define _ZJ_TRACE_T_IF(condition, intervalS, msg, ...) _ZJ_MSG_IF(condition, ZjL::Trace, intervalS, msg, ##__VA_ARGS__)

#define _ZJ_DEBUG(msg, ...) _ZJ_MSG(ZjL::Debug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T(intervalS, msg, ...) _ZJ_MSG_T(ZjL::Debug, intervalS, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Debug, msg, ##__VA_ARGS__)
#define _ZJ_DEBUG_T_IF(condition, intervalS, msg, ...) _ZJ_MSG_IF(condition, ZjL::Debug, intervalS, msg, ##__VA_ARGS__)

#define _ZJ_INFO(msg, ...) _ZJ_MSG(ZjL::Info, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T(intervalS, msg, ...) _ZJ_MSG_T(ZjL::Info, intervalS, msg, ##__VA_ARGS__)
#define _ZJ_INFO_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Info, msg, ##__VA_ARGS__)
#define _ZJ_INFO_T_IF(condition, intervalS, msg, ...) _ZJ_MSG_IF(condition, ZjL::Info, intervalS, msg, ##__VA_ARGS__)

#define _ZJ_WARN(msg, ...) _ZJ_MSG(ZjL::Warn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T(intervalS, msg, ...) _ZJ_MSG_T(ZjL::Warn, intervalS, msg, ##__VA_ARGS__)
#define _ZJ_WARN_IF(condition, msg, ...) _ZJ_MSG_IF(condition, ZjL::Warn, msg, ##__VA_ARGS__)
#define _ZJ_WARN_T_IF(condition, intervalS, msg, ...) _ZJ_MSG_IF(condition, ZjL::Warn, intervalS, msg, ##__VA_ARGS__)
