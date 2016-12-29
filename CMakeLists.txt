cmake_minimum_required (VERSION 3.6)
project (capstone)

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -std=gnu11 -g")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=gnu++14 -pthread")

add_definitions(-DASIO_STANDALONE)
include_directories("asio/asio/include/")

add_subdirectory(source/butler)

