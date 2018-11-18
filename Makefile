SRC_DIR = .
LIB_DIR = lib

G++ = g++ -g -std=c++11 -Werror -o

all: format test clean

format:
	clang-format -i *.cc *.h

clean:
	rm -rf *.out
	rm -rf *.dSYM/

test:
	$(G++) tests.out test.cc -I ./$(LIB_DIR)/catch/ -I $(SRC_DIR)
	./tests.out $(TEST_TAGS)

bench:
	$(G++) bench.out bench.cc -I $(SRC_DIR)
	./bench.out
