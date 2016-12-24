cmake_minimum_required(VERSION 3.6)

add_executable(butler-test-suite main.cpp log.cpp ${GTEST_DIR}/src/gtest-all.cc)
include_directories("${PROJECT_SOURCE_DIR}/source/butler" ${GTEST_DIR} ${GTEST_DIR}/include)

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(butler-test-suite butler ${Boost_LIBRARIES})

