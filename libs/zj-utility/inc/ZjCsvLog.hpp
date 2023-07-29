#pragma once

#include "ZjSingleton.hpp"
#include "ZjConcepts.hpp"

#include <unordered_map>
#include "Eigen/Eigen"
#include "spdlog/spdlog.h"

class ZjCsvLog : public ZjSingleton<ZjCsvLog>
{
private:
    class ZjCsvLogSingleFile
    {
    public:
        ZjCsvLogSingleFile() = default;
        ~ZjCsvLogSingleFile() = default;

        void log();
    };

private:
    using Filename = std::string;
    using Size = Eigen::Index;

    template <ZjArithmetic T>
    using EigenVecX = Eigen::Matrix<T, Eigen::Dynamic, 1>;

public:
    /// give it a dedicated thread
    void init();

    template <ZjArithmetic T>
    void log(const Filename& filename, const EigenVecX<T>& data)
    {
    }

    void finish(const Filename& filename);

private:
    std::unordered_map<Filename, ZjCsvLogSingleFile> m_logMap;
};