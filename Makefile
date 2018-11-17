UNAME := $(shell uname)

SRC_DIR = .
LIB_DIR = lib
TEST_DIR = test

# -g -> generate debug info
# -Werror -> treat every warning as an error
G++ = g++ -g -std=c++11 -Werror -o

ifeq ($(UNAME), Linux)
CLANG_FORMAT_BIN = clang-format-4.0
endif
ifeq ($(UNAME), Darwin)
CLANG_FORMAT_BIN = clang-format
endif

all: format test

format:
	$(CLANG_FORMAT_BIN) -i *.cc
	$(CLANG_FORMAT_BIN) -i *.h

clean:
	rm -rf *.out
	rm -rf *.dSYM/

.PHONY: test
test:
	$(G++) tests.out test.cc -I ./$(LIB_DIR)/catch/ -I .
	./tests.out $(TEST_TAGS)

benchmark:
	$(G++) main.out main.cc -I .
	./main.out
