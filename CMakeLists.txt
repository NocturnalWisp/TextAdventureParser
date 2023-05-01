cmake_minimum_required(VERSION 3.0.0)
project(TAP VERSION 0.1.0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/game.ta
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(TAP main.cpp ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
