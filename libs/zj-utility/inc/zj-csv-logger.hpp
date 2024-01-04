/**
 * @file zj-csv-logger.hpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#pragma once

#include "zj-singleton.hpp"
#include "zj-concepts.hpp"
#include "zj-logging-macros.hpp"
#include "zj-debug.hpp"

#include <unordered_map>
#include <sstream>
#include <utility>
#include <string>

#include "Eigen/Dense"
#include "spdlog/spdlog.h"

/// @brief A csv log class that can create and log to as many files as needed in a thread safe fashion
class ZjCsvLogger : public ZjSingleton<ZjCsvLogger>
{
    using CoreLogPtr = ZjLogger::CoreLogPtr;
    using LogName = std::string;

    using DataSize = Eigen::Index;
    using DataDimension = decltype(Eigen::Dynamic);

    /// Eigen vector alias
    template <ZjArithmetic T, DataDimension N = Eigen::Dynamic>
    requires ZjEigenSizeValid<N>
    using EigenVec = Eigen::Matrix<T, N, 1>;

private:
    /// @brief A inner class that represents a logger that only logs data to a single file for the outer class to create and employ
    class ZjCsvLoggingUnit
    {
        /// @see https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
        const Eigen::IOFormat eigen_fmt_ {9, 0, ", "};

    public:
        ZjCsvLoggingUnit() = default;
        ~ZjCsvLoggingUnit() = default;

        /// @note https://github.com/cpp-best-practices/cppbestpractices/blob/master/08-Considering_Performance.md#enable-move-operations
        /// @note https://en.cppreference.com/w/cpp/language/move_constructor, enabling move constructor for default shallow coping
        /// @see Employed by ZjCsvLogger::log
        ZjCsvLoggingUnit(ZjCsvLoggingUnit&&) = default;

        /**
         * @brief Log data, it will check to make sure each time the data to be logged is consistent with previous data's dimension
         *
         * @tparam T Data type
         * @tparam N Data dimension
         * @param log_name Log name
         * @param data Data
         *
         * @note If the given log name doesn't exist, it will initialized the log and file and log the data; otherwise, data will be logged
         * to the existing log and file
         *
         * @note This is managed by the outer class, the outer class will always use the same log name to access a ZjCsvLoggingUnit
         * instance; technically, if this class takes a new log name, the existing one will be overwritten, but the outer class won't do
         * that
         */
        template <ZjArithmetic T, DataDimension N>
        void Log(const std::string& log_name, const EigenVec<T, N>& data)
        {
            // Create a log if not already exists
            if (!logger_) [[unlikely]] { Init(log_name, data.size()); }

            _ZJ_THROW_IF(data.size() != data_size_, "inconsistent data size [{} | {}]", data.size(), data_size_);
            std::ostringstream oss;
            oss << data.transpose().format(eigen_fmt_);
            logger_->info("{}", oss.str());
        }

        /// Log's file name
        const std::string& Filename() const { return filename_; }

    private:
        /// @brief Initialize the logger with a name, and the size of data to-be logged to keep track of data consistence
        void Init(const std::string& log_name, const DataSize data_size);

        CoreLogPtr logger_;
        DataSize data_size_;

        std::string log_name_;
        std::string filename_;
    };

public:
    /**
     * @brief Log data, if the given log name doesn't exist, it create the log and file and log the data; otherwise data will be logged to
     * the existing log and file
     *
     * @tparam T Data type
     * @tparam N Data dimension
     * @param log_name Log name
     * @param data Data
     */
    template <ZjArithmetic T, DataDimension N>
    void Log(const std::string& log_name, const EigenVec<T, N>& data)
    {
        /// @note `logging_units_` is a map, it will automatically handle/ignore duplication, no need to manually search here
        /// @note https://stackoverflow.com/a/27553958, with default move constructor, it will be moved
        logging_units_.emplace(log_name, ZjCsvLoggingUnit {});
        logging_units_.at(log_name).Log(log_name, data);
    }

    /// Drop a given log if it exists
    void Drop(const std::string& log_name);

    /// Number of active logs at the moment
    inline auto NumLogs() const { return logging_units_.size(); }

    /// Get a log's file name
    std::string Filename(const std::string& log_name);

private:
    /// A map that keeps track of ZjCsvLoggingUnit by their unique log name
    std::unordered_map<LogName, ZjCsvLoggingUnit> logging_units_;
};
