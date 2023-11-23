/**
 * @file zj-verify-numerics.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-concepts.hpp"
#include "zj-debug.hpp"
#include "zj-formatters.hpp"

#include <type_traits>
#include <sstream>
#include <string>
#include <utility>
#include <cmath>

#include "Eigen/Dense"

/**
 * @brief Verify if an eigen matrix has NAN of INF entries
 * @note Client code should not use this function directly, use _ZJ_VERIFY instead
 *
 * @tparam Type Data type
 * @tparam M Number of rows
 * @tparam N Number of columns
 * @param[in] var Variable
 * @param[in] var_literal Variable literal
 * @param[in] varSource Variable source location
 *
 * @see Keyword `requires` https://en.cppreference.com/w/cpp/language/constraints#Conjunctions
 */
template <ZjArithmetic Type, decltype(Eigen::Dynamic) M, decltype(Eigen::Dynamic) N>
requires ZjEigenSizeValid<M> && ZjEigenSizeValid<N>
void _ZjVerifyNumerics(const Eigen::Matrix<Type, M, N>& var, const std::string& var_literal, const std::source_location& s)
{
    if (var.array().isNaN().any() || var.array().isInf().any()) {
        std::ostringstream oss;
        Eigen::IOFormat kEigenFmt {Eigen::StreamPrecision, 0, ", "};
        if (var.cols() == 1) {
            oss << var.transpose().format(kEigenFmt);
        } else {
            oss << var.format(kEigenFmt);
        }

        std::string err_msg {fmt::format("singular eigen variable [{}]\n{}", var_literal, oss.str())};
        std::string fmt_msg {fmt::format(zj::kTraceFmt, s.file_name(), s.line(), s.column(), s.function_name(), err_msg)};
        _ZjThrow(ZjE::kSingularity, ZjSingularity(std::move(fmt_msg)), s, err_msg);
    }
}

/**
 * @brief Verify if a scalar is normal
 * @note Client code should not use this function directly, use _ZJ_VERIFY instead
 *
 * @tparam Type Data type
 * @param[in] var Variable
 * @param[in] var_literal Variable literal
 * @param[in] s Variable source location
 */
template <ZjArithmetic Type>
void _ZjVerifyNumerics(const Type var, const std::string& var_literal, const std::source_location& s)
{
    if (!std::isnormal(var)) {
        std::string err_msg {fmt::format("singular std variable [{} = {}]", var_literal, var)};
        std::string fmt_msg {fmt::format(zj::kTraceFmt, s.file_name(), s.line(), s.column(), s.function_name(), err_msg)};
        _ZjThrow(ZjE::kSingularity, ZjSingularity(std::move(fmt_msg)), s, err_msg);
    }
}

/// A macro wrapper for _ZjVerifyNumerics with variable literal and source location information
#define _ZJ_VERIFY(variable) _ZjVerifyNumerics(variable, #variable, std::source_location::current())
