/**
 * @file zj-formatters.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-11
 * @copyright Copyright 2023 by Zongyao Jin
 */

#pragma once

namespace zj {

constexpr const char* kTraceFmt {"{}:{}:{} @ `{}` | {}"};
constexpr const char* kAssertFmt {"{}:{}:{} @ `{}` | [{}]\n  {}\n"};

} // namespace zj
