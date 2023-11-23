# Use the folder name as the executable name
get_filename_component(exampleName ${CMAKE_CURRENT_LIST_DIR} NAME)

# Collect source files
file(GLOB exampleSources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# Add the execuatable
add_executable(${exampleName} main.cpp ${exampleSources})

# * Add include folders
# * I want to install the executable, but not its include directories, applying PRIVATE here so the paths can be
#   absolute; otherwise, they will have to be relative paths via generator expressions for the install commands to parse
#   and install
target_include_directories(${exampleName} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

# Link interal libraries
target_link_libraries(${exampleName} PRIVATE zj-log-interface)

# Find and link external packages
find_package(Eigen3 REQUIRED)
# Applying PRIVATE here for the same reason as in target_include_directories() above
target_link_libraries(${exampleName} PRIVATE Eigen3::Eigen)
