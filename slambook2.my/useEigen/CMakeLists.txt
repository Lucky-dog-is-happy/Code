cmake_minimum_required(VERSION 4.1)

project(useEigen LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Release")
set(CMKAE_CXX_FLAGS "-O3")

include_directories("/usr/include/eigen3")
add_executable(eigenMatrix eigenMatrix.cc)
