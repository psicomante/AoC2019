cmake_minimum_required(VERSION 3.15)
project(AoC2019)

set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/day01/d1p1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/day02/d2p1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/day03/d3p1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/day05/d5p1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(d0p1 day00/d0p1.cpp)
add_executable(d1p1 day01/d1p1.cpp day01/d1p1.txt)
add_executable(d1p2 day01/d1p2.cpp)
add_executable(d2p1 day02/d2p1.cpp day02/d2p1.txt InputIO.h day02/program.h)
add_executable(d2p2 day02/d2p2.cpp)
add_executable(d3p1 day03/d3p1.cpp day03/d3p1.txt InputIO.h)
add_executable(d4p1 day04/d4p1.cpp InputIO.h)
add_executable(d5p1 day05/d5p1.cpp InputIO.h day05/d5p1.txt)