cmake_minimum_required(VERSION 3.6)

add_library(test-c-linkage STATIC c-linkage.c)

#find_package(GTest REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/source/saffronsnail/butler" ${GTEST_DIR}
                     ${GTEST_DIR}/include
                   )

add_executable(butler-test-suite main.cpp log.cpp ${GTEST_DIR}/src/gtest-all.cc)
target_link_libraries(butler-test-suite butler test-c-linkage)

