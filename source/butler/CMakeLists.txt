cmake_minimum_required(VERSION 3.6)

add_library(butler entrance-protocol.cpp utils.c)

add_subdirectory(test)

