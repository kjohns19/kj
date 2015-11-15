cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(kjtests)

find_package(GTest REQUIRED)

include_directories(/home/kevin/programming/c++/kj/src src ${GTEST_INCLUDE_DIRS})
link_directories(/home/kevin/programming/c++/kj)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

file(GLOB_RECURSE TESTS src/*.cpp)

foreach(test ${TESTS})
    get_filename_component(exename ${test} NAME_WE)
    add_executable(${exename} ${test})
    target_link_libraries(${exename} kj ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRAREIS} pthread)
endforeach(test)
