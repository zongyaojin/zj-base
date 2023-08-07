# Use the folder name as the executable name
get_filename_component(exampleName ${CMAKE_CURRENT_LIST_DIR} NAME)

# Collect source files
file(GLOB exampleSources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# Add the execuatable
add_executable(${exampleName} main.cpp ${exampleSources})

# Add include folders, applying PRIVATE since they don't have to be exposed for installation
target_include_directories(${exampleName} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

# Link interal libraries, applying PRIVATE since they don't have to be exposed for installation
target_link_libraries(${exampleName} PRIVATE zj-all-headers gcov)
