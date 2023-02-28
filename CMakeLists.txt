cmake_minimum_required(VERSION 3.24)
project(3D)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES    sources/*.cpp sources/*.c)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

include_directories(include)
include_directories(include/SDL2)
add_executable(3D ${SOURCES} ${HEADERS})