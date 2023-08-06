# ######################################################################################################################
# * Example of an independent client project
# ######################################################################################################################

cmake_minimum_required(VERSION 3.22.1)
project(client-project-example)

# zj-base requires modern c and cpp compiler standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_compile_definitions(__EXAMPLE_PKG_BUILD_PATH__="${CMAKE_BINARY_DIR}")

add_executable(${PROJECT_NAME} main.cpp)

find_package(zj-base REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC zj-base::zj-base)
