# set app name as the folder
get_filename_component(APP_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

# use it as the project name
project(${APP_NAME})

# use it as the executable name
add_executable(${APP_NAME} main.cpp)

find_package(Boost REQUIRED)

# add include folder, for the Boost::assert library, see https://stackoverflow.com/a/26752110/6291896
target_include_directories(${APP_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc
                                              ${Boost_INCLUDE_DIRS})

# source files
file(GLOB APP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# ##############################################################################
# find external dependencies
find_package(RBDyn REQUIRED)
find_package(pinocchio REQUIRED)
# ##############################################################################

# link it against internal libraries
target_link_libraries(
  ${APP_NAME}
  PUBLIC ZjBase
         RBDyn::RBDyn
         RBDyn::Parsers
         pinocchio::pinocchio)
