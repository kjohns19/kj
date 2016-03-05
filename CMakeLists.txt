cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(kj)

find_package(GTest REQUIRED)

INCLUDE(FindPkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})

file(GLOB_RECURSE SRC_FILES_kj src/*.cpp)
add_library(kj STATIC ${SRC_FILES_kj})
target_compile_options(kj PRIVATE -std=c++14 -g -Wall -Werror)
target_include_directories(kj PRIVATE ${GTKMM_INCLUDE_DIRS} src)
target_link_libraries(kj ${GTKMM_LIBRARIES})

file(GLOB_RECURSE SRC_FILES_kjtests test/*.cpp)
add_executable(kjtests ${SRC_FILES_kjtests})
target_compile_options(kjtests PRIVATE -std=c++14 -g -Wall -Werror)
target_include_directories(kjtests PRIVATE ${GTEST_INCLUDE_DIRS} test src)
target_link_libraries(kjtests kj ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

install(TARGETS kj ARCHIVE DESTINATION lib)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
