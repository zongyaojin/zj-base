get_filename_component(zjTest ${CMAKE_CURRENT_LIST_DIR} NAME)

set(testSrc ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(${zjTest} ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${testSrc})

# ######################################################################################################################
# Previously set a separate folder for the test because it requires Boost::filesystem, but the dependency was removed by
# std::filesystem
# ######################################################################################################################

# find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(${zjTest} PUBLIC ${PROJECT_NAME}::${PROJECT_NAME} GTest::GTest GTest::Main gcov # Boost::filesystem
)

set_target_properties(${zjTest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/${zjTest})
add_test(NAME ${zjTest} COMMAND ${CMAKE_BINARY_DIR}/tests/${zjTest}/${zjTest})
