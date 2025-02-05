cmake_minimum_required(VERSION 3.18)

# Find or fetch Google Test
include(FetchContent)

FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc898e2951020cbdca1304b75f5950d1f59 # v1.15.2
)

FetchContent_MakeAvailable(GoogleTest)

add_executable(test_list_solution list.cpp)
target_link_libraries(test_list_solution PRIVATE
    ${PROJECT_NAME}
    gtest
    gtest_main
)
add_executable(test_matrix_solution list.cpp)
target_link_libraries(test_matrix_solution PRIVATE
    ${PROJECT_NAME}
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_list_solution)
gtest_discover_tests(test_matrix_solution)