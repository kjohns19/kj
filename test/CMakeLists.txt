cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(kjtests)

find_package(GTest REQUIRED)

include_directories(src ${GTEST_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror")

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(kjtests ${SRC_FILES})

target_link_libraries(kjtests kj ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
