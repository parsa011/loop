COMPILER = clang
TEST = $(filter-out src/loop.cpp, $(wildcard src/*.cpp)) $(wildcard test/*.cpp)
SRC = $(wildcard src/*.cpp)
WARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Werror
FLAGS_DEBUG = -D DEBUG -g -O0  -std=c++17
FLAGS_RELEASE = -O3 -std=c++17
FLAGS_TEST = -g -O0 -std=c++17
LDFLAGS = -pthread -ldl -lm -lstdc++

.PHONY: all test clean

test:
	$(COMPILER) $(TEST) $(WARNINGS) $(FLAGS_TEST) $(LDFLAGS) -o loop-test

debug:
	$(COMPILER) $(SRC) $(WARNINGS) $(FLAGS_DEBUG) $(LDFLAGS) -o loop

release:
	$(COMPILER) $(SRC) $(WARNINGS) $(FLAGS_RELEASE) $(LDFLAGS) -o loop

all: debug test

clean:
	rm -f -- loop
	rm -f -- loop-test

install: release
	ln -sf $PWD/loop ~/.local/bin/loop;