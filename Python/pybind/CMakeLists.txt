cmake_minimum_required(VERSION 3.0)

project(MonteCarloPi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

find_package(Threads)

add_subdirectory(pybind11)

include_directories(
    "."
    "./pybind11"
)

set(SOURCE
    MonteCarloPi.cpp
)

pybind11_add_module(${PROJECT_NAME} ${SOURCE})