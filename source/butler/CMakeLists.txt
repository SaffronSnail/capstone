cmake_minimum_required(VERSION 3.6)

add_library(networking networking.c utils.c)
add_library(butler entrance-protocol.c)

add_subdirectory(test)

