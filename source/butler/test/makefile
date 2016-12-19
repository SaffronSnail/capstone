GTEST_DIR=/usr/local/src/googletest/googletest/

test: test.out
	./test.out

test.out: main.cpp log.cpp networking.gtest ../../build/networking.o ../../build/utils.o
	g++ main.cpp log.cpp ../../build/networking.o ../../build/utils.o ${GTEST_DIR}/src/gtest-all.cc -I${GTEST_DIR} -isystem ${GTEST_DIR}/include -pthread -I ../../source/butler -o test.out -Wall -Wextra -Werror -std=c++14 -g

