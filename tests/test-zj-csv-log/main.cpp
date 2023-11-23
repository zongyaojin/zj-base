#include "gtest/gtest.h"

#include "zj-csv-logger.hpp"
#include "zj-logging-macros-simplified.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

#include "Eigen/Dense"

namespace fs = std::filesystem;

bool printFile(const std::string& Filename)
{
    std::stringstream ss;

    ss << std::endl << "---------- ---------- ----------" << std::endl;
    ss << "Printing file: " << Filename << std::endl;
    fs::path file_path(Filename);

    // Check if the file exists and is a regular file
    if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
        std::cerr << "Error: The specified file does not exist or is not a regular file." << std::endl;
        return false;
    }

    // Open the file using ifstream
    std::ifstream file_stream(file_path.string());

    // Check if the file is successfully opened
    if (!file_stream.is_open()) {
        std::cerr << "Error: Failed to open the file." << std::endl;
        return false;
    }

    // Read and print the content of the file
    std::string line;
    while (std::getline(file_stream, line)) {
        ss << line << std::endl;
    }

    ss << "---------- ---------- ----------" << std::endl;
    std::cout << ss.str() << std::endl;
    return true;
}

TEST(TestZjCsvLog, TestZjCsvLog)
{
    std::string log1 {"log1"};
    std::string log2 {"log2"};

    Eigen::Matrix<double, Eigen::Dynamic, 1> v1, v2, v3;
    v1.resize(3);
    v2.resize(3);
    v3.resize(3);
    v1 << 1, 2, 3;
    v2 << 10, 20, 30;
    v3 << 100, 200, 300;

    Eigen::Vector4d v4, v5, v6;
    v4 << 4, 3, 2, 1;
    v5 << 40, 30, 20, 10;
    v6 << 400, 300, 200, 100;

    ZjCsvLogger::GetInstance().Log(log1, v1);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);
    ZjCsvLogger::GetInstance().Log(log1, v2);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);
    ZjCsvLogger::GetInstance().Log(log1, v3);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);

    std::string log1_fileName = ZjCsvLogger::GetInstance().Filename(log1);
    _ZJ_DEBUG("log 1 file: [{}]", log1_fileName);

    ZjCsvLogger::GetInstance().Log(log2, v4);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 2);

    ZjCsvLogger::GetInstance().Drop(log1);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);

    ZjCsvLogger::GetInstance().Log(log2, v5);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);
    ZjCsvLogger::GetInstance().Log(log2, v6);
    EXPECT_EQ(ZjCsvLogger::GetInstance().NumLogs(), 1);

    std::string log2_fileName = ZjCsvLogger::GetInstance().Filename(log2);
    _ZJ_DEBUG("log 2 file: [{}]", log2_fileName);

    EXPECT_TRUE(fs::exists(log1_fileName));
    EXPECT_TRUE(fs::exists(log2_fileName));

    EXPECT_TRUE(printFile(log1_fileName));
    EXPECT_TRUE(printFile(log2_fileName));

    EXPECT_THROW(ZjCsvLogger::GetInstance().Log(log2, v1), ZjFault);
}
