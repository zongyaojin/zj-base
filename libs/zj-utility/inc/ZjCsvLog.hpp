#pragma once

#include "ZjSingleton.hpp"
#include "ZjConcepts.hpp"
#include "ZjLogMacros.hpp"
#include "ZjDebug.hpp"

#include <unordered_map>
#include <sstream>

#include "Eigen/Eigen"
#include "spdlog/spdlog.h"

class ZjCsvLog : public ZjSingleton<ZjCsvLog>
{
    using CoreLogPtr = ZjLog::CoreLogPtr;
    using LogName = std::string;

    using DataSize = Eigen::Index;
    using DataDimension = decltype(Eigen::Dynamic);

    template <ZjArithmetic T, DataDimension N = -1>
    using EigenVec = Eigen::Matrix<T, N, 1>;

private:
    class ZjCsvLogWorker
    {
        /// @see https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
        const Eigen::IOFormat k_eigenFmt {9, 0, ", "};

    public:
        ZjCsvLogWorker() = default;
        ~ZjCsvLogWorker() = default;

        void init(const std::string& logName, const DataSize dataSize);

        template <ZjArithmetic T, DataDimension N>
        void log(const std::string& logName, const EigenVec<T, N>& data)
        {
            if (!m_logger) {
                init(logName, data.size());
            }

            _ZJ_THROW_IF(data.size() != m_dataSize, "inconsistent data size [{} | {}]", data.size(), m_dataSize);
            std::ostringstream oss;
            oss << data.transpose().format(k_eigenFmt);
            m_logger->info("{}", oss.str());
        }

        const std::string& fileName() const { return m_fileName; }

    private:
        CoreLogPtr m_logger;
        DataSize m_dataSize;

        std::string m_logName;
        std::string m_fileName;
    };

public:
    template <ZjArithmetic T, DataDimension N>
    void log(const std::string& logName, const EigenVec<T, N>& data)
    {
        if (m_logWorkerMap.find(logName) != m_logWorkerMap.end()) {
            m_logWorkerMap.at(logName).log(logName, data);
            return;
        }

        m_logWorkerMap.emplace(logName, ZjCsvLogWorker {});
        m_logWorkerMap.at(logName).log(logName, data);
    }

    void drop(const std::string& logName);

    inline auto numLogs() const { return m_logWorkerMap.size(); }

    std::string fileName(const std::string& logName);

private:
    std::unordered_map<LogName, ZjCsvLogWorker> m_logWorkerMap;
};