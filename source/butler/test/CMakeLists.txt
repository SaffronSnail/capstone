cmake_minimum_required(VERSION 3.6)

add_executable(butler-test-suite main.cpp log.cpp ${GTEST_DIR}/src/gtest-all.cc)
target_link_libraries(butler-test-suite networking)
include_directories("${PROJECT_SOURCE_DIR}/source/butler" ${GTEST_DIR} ${GTEST_DIR}/include)

