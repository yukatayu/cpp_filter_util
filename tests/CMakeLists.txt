cmake_minimum_required(VERSION 2.6)
project(cpp_filter_lib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(FILTER_LIB_TEST "Filter Library Check" OFF)

enable_testing()
add_executable(test_main test.cpp)
add_test(test_main test_main)
target_include_directories(test_main
	PUBLIC ${PROJECT_SOURCE_DIR}/../
)