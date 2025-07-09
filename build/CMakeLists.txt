cmake_minimum_required(VERSION 3.25)
project(vectortools_cxx LANGUAGES CXX)

set_property(CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS "11" "14" "17" "20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS
	"Configuring project to build with C++ standard: ${CMAKE_CXX_STANDARD}")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_library(vtool_lib INTERFACE)
target_include_directories(vtool_lib INTERFACE SRC_DIR)

add_executable(vtool_test "${SRC_DIR}/vectortools_test.cpp")
target_link_libraries(vtool_test PRIVATE vtool_lib)
