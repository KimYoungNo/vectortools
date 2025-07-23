cmake_minimum_required(VERSION 3.25)
project(vectortools_cxx LANGUAGES CXX)

set_property(CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS "11" "14" "17" "20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(vtool_lib INTERFACE)
target_include_directories(vtool_lib INTERFACE "../src")

add_executable(vtool_test "main_test.cpp")
target_link_libraries(vtool_test PRIVATE vtool_lib)
