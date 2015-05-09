cmake_minimum_required(VERSION 3.2)
project(SWE_Projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(SWE_Projekt ${SOURCE_FILES})