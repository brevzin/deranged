cmake_minimum_required(VERSION 3.15)
project(deranged)

add_library(deranged INTERFACE)
target_include_directories(deranged INTERFACE include)

enable_testing()
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_subdirectory(test)
