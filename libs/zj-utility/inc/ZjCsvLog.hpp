/**
 * @file ZjCsvLog.hpp
 *
 * @brief Csv log utility class
 *
 * @author Zongyao Jin
 * @date 2023-08-08
 */

#pragma once

#include "ZjSingleton.hpp"
#include "ZjConcepts.hpp"
#include "ZjLogMacros.hpp"
#include "ZjDebug.hpp"

#include <unordered_map>
#include <sstream>
#include <utility>
#include <string>

#include "Eigen/Eigen"
#include "spdlog/spdlog.h"

/// @brief A csv log class that can create and log to as many files as needed in a thread safe fashion
class ZjCsvLog : public ZjSingleton<ZjCsvLog>
{
    using CoreLogPtr = ZjLog::CoreLogPtr;
    using LogName = std::string;

    using DataSize = Eigen::Index;
    using DataDimension = decltype(Eigen::Dynamic);

    /**
     * @brief Eigen vector alias
     *
     * @tparam T Numeric data type
     * @tparam N Vector dimension
     *
     * @see For the constraint with keyword `requires`, https://en.cppreference.com/w/cpp/language/constraints#Conjunctions
     * @note To reuse the constraint, one can do:
     * ```cpp
     *      template <decltype(Eigen::Dynamic) N>
     *      concept DataDimensionValid = (N != 0) && (N > -2);
     *
     *      template <ZjArithmetic T, DataDimension N = Eigen::Dynamic>
     *      requires zj::csv::log::DataDimensionValid<N>
     *      using EigenVec = Eigen::Matrix<T, N, 1>;
     * ```
     */
    template <ZjArithmetic T, DataDimension N = Eigen::Dynamic>
    requires(N != 0 && N > -2) using EigenVec = Eigen::Matrix<T, N, 1>;

private:
    /// @brief A inner class that represents a logger that only logs data to a single file for the outer class to create and employ
    class ZjCsvLogWorker
    {
        /// @see https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
        const Eigen::IOFormat k_eigenFmt {9, 0, ", "};

    public:
        ZjCsvLogWorker() = default;
        ~ZjCsvLogWorker() = default;

        /// @note https://github.com/cpp-best-practices/cppbestpractices/blob/master/08-Considering_Performance.md#enable-move-operations
        /// @note https://en.cppreference.com/w/cpp/language/move_constructor, enabling move constructor for default shallow coping
        /// @see Employed by ZjCsvLog::log
        ZjCsvLogWorker(ZjCsvLogWorker&&) = default;

        /**
         * @brief Log data, it will check to make sure each time the data to be logged is consistent with previous data's dimension
         *
         * @tparam T Data type
         * @tparam N Data dimension
         * @param logName Log name
         * @param data Data
         *
         * @note If the given log name doesn't exist, it will initialized the log and file and log the data; otherwise, data will be logged
         * to the existing log and file
         *
         * @note This is managed by the outer class, the outer class will always use the same log name to access a ZjCsvLogWorker instance;
         * technically, if this class takes a new log name, the existing one will be overwritten, but the outer class won't do that
         */
        template <ZjArithmetic T, DataDimension N>
        void log(const std::string& logName, const EigenVec<T, N>& data)
        {
            // Create a log if not already exists
            if (!m_logger) [[unlikely]] {
                init(logName, data.size());
            }

            _ZJ_THROW_IF(data.size() != m_dataSize, "inconsistent data size [{} | {}]", data.size(), m_dataSize);
            std::ostringstream oss;
            oss << data.transpose().format(k_eigenFmt);
            m_logger->info("{}", oss.str());
        }

        /// Log's file name
        const std::string& fileName() const { return m_fileName; }

    private:
        /// @brief Initialize the logger with a name, and the size of data to-be logged to keep track of data consistence
        void init(const std::string& logName, const DataSize dataSize);

        CoreLogPtr m_logger;
        DataSize m_dataSize;

        std::string m_logName;
        std::string m_fileName;
    };

public:
    /**
     * @brief Log data, if the given log name doesn't exist, it create the log and file and log the data; otherwise data will be logged to
     * the existing log and file
     *
     * @tparam T Data type
     * @tparam N Data dimension
     * @param logName Log name
     * @param data Data
     */
    template <ZjArithmetic T, DataDimension N>
    void log(const std::string& logName, const EigenVec<T, N>& data)
    {
        /// @note `m_logWorkerMap` is a map, it will automatically handle/ignore duplication, no need to manually search here
        /// @note https://stackoverflow.com/a/27553958, with default move constructor, it will be moved
        m_logWorkerMap.emplace(logName, ZjCsvLogWorker {});
        m_logWorkerMap.at(logName).log(logName, data);
    }

    /// Drop a given log if it exists
    void drop(const std::string& logName);

    /// Number of active logs at the moment
    inline auto numLogs() const { return m_logWorkerMap.size(); }

    /// Get a log's file name
    std::string fileName(const std::string& logName);

private:
    /// A map that keeps track of ZjCsvLogWorker by their unique log name
    std::unordered_map<LogName, ZjCsvLogWorker> m_logWorkerMap;
};
