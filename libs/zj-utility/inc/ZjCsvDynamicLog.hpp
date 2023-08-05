#pragma once

#include "ZjSingleton.hpp"
#include "ZjConcepts.hpp"
#include "ZjLogMacros.hpp"
#include "ZjDebug.hpp"

#include <unordered_map>
#include <sstream>

#include "Eigen/Eigen"
#include "spdlog/spdlog.h"

class ZjCsvDynamicLog : public ZjSingleton<ZjCsvDynamicLog>
{
    using CoreLogPtr = ZjLog::CoreLogPtr;
    using DataSize = Eigen::Index;
    using LogName = std::string;

    template <ZjArithmetic T>
    using EigenVecX = Eigen::Matrix<T, Eigen::Dynamic, 1>;

private:
    class ZjCsvDynamicLogWorker
    {
        /// @note https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
        const Eigen::IOFormat k_eigenFmt {9, 0, ", "};

    public:
        ZjCsvDynamicLogWorker(const std::string& logName, const DataSize dataSize);
        ~ZjCsvDynamicLogWorker() = default;

        template <ZjArithmetic T>
        void log(const EigenVecX<T>& data)
        {
            _ZJ_THROW_IF(data.size() != m_dataSize, "inconsistent data size [{} | {}]", data.size(), m_dataSize);
            std::ostringstream oss;
            oss << data.transpose().format(k_eigenFmt);
            m_logger->info("{}", oss.str());
        }

        const std::string& fileName() const { return m_fileName; }

    private:
        CoreLogPtr m_logger;
        DataSize m_dataSize;
        std::string m_fileName;
    };

public:
    template <ZjArithmetic T>
    void log(const std::string& logName, const EigenVecX<T>& data)
    {
        if (m_logWorkerMap.find(logName) != m_logWorkerMap.end()) {
            m_logWorkerMap.at(logName).log(data);
            return;
        }

        m_logWorkerMap.emplace(logName, ZjCsvDynamicLogWorker {logName, data.size()});
        m_logWorkerMap.at(logName).log(data);
    }

    void drop(const std::string& logName);

    inline auto numLogs() const { return m_logWorkerMap.size(); }

    std::string fileName(const std::string& logName);

private:
    std::unordered_map<LogName, ZjCsvDynamicLogWorker> m_logWorkerMap;
};