cmake_minimum_required(VERSION 3.19.0)

project(hc_datastructs VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

if(NOT HC_SKIP_TESTS)
    find_package(GTest 1.10.0 REQUIRED)
    include(GoogleTest)
    enable_testing()
endif()

add_subdirectory(vector)
