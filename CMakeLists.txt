cmake_minimum_required(VERSION 3.0)
project(exifpp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(exifpp-app main.cpp exifpp.h exifpp.cpp)
