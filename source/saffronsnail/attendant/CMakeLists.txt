cmake_minimum_required(VERSION 3.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/attendant")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/attendant")

#add_library(attendant-dummy SHARED dummy.cpp)
add_library(attendant-echo SHARED echo.cpp)

