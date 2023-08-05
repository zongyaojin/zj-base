#pragma once

#include "ZjSingleton.hpp"
#include "ZjConcepts.hpp"
#include "ZjLogsManager.hpp"
#include "ZjLogMacros.hpp"

#include <unordered_map>
#include <sstream>

#include "Eigen/Eigen"
#include "spdlog/spdlog.h"

class ZjCsvLog : public ZjSingleton<ZjCsvLog>
{
    using CoreLogLevel = ZjLogsManager::CoreLogLevel;
    using CoreLogPtr = ZjLogsManager::CoreLogPtr;

    using Filename = std::string;
    using DataSize = Eigen::Index;

    template <ZjArithmetic T>
    using EigenVecX = Eigen::Matrix<T, Eigen::Dynamic, 1>;

private:
    class ZjCsvLogSingleFile
    {
        const Eigen::IOFormat k_csvFmt {Eigen::StreamPrecision, 0, ", "};

    public:
        ZjCsvLogSingleFile() = default;
        ~ZjCsvLogSingleFile() = default;

        template <ZjArithmetic T>
        void log(const Filename& filename, const EigenVecX<T>& data)
        {
            if (m_logger) {
                _ZJ_ASSERT(data.size() == m_dataSize, "inconsistent data size");
                std::ostringstream oss;
                oss << data.format(k_csvFmt);
                m_logger->info("{}", oss.str());
                return;
            }

            init(filename, data.size());
        }

        void init(const Filename& filename, const DataSize dataSize);

    private:
        CoreLogPtr m_logger;
        DataSize m_dataSize {0};
        std::ostringstream m_oss;
    };

public:
    template <ZjArithmetic T>
    void log(const Filename& filename, const EigenVecX<T>& data)
    {
        if (m_logMap.find(filename) != m_logMap.end()) {
            m_logMap.at(filename).log(filename, data);
            return;
        }

        m_logMap.emplace(filename, ZjCsvLogSingleFile {});
        m_logMap.at(filename).log(filename, data);
    }

    void finish(const Filename& filename);

private:
    std::unordered_map<Filename, ZjCsvLogSingleFile> m_logMap;
};