cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(src)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror")

project(kj)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(kj STATIC ${SRC_FILES})
