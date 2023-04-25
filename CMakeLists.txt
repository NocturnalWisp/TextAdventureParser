cmake_minimum_required(VERSION 3.0.0)
project(TAP VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(TAP main.cpp ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
