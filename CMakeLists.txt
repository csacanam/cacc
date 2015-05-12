cmake_minimum_required(VERSION 3.2)
project(CACC_Library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CustomAppLayer.cc
    CustomAppLayer.h
    NodeInfo.cc
    NodeInfo.h)

add_executable(CACC_Library ${SOURCE_FILES} Main.cpp Main.h)