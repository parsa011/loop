COMPILER = clang
TEST = $(filter-out src/main.cpp, $(wildcard src/*.cpp)) $(wildcard test/*.cpp)
SRC = $(wildcard src/*.cpp)
STD = -std=c++20
WARNINGS = -Wall -Wextra -Wpedantic -Werror
FLAGS_DEBUG = -D DEBUG -g -O0  -std=c++20
FLAGS_RELEASE = -O3
FLAGS_TEST = -g -O0
LD = -pthread -ldl -lm -lstdc++ -I include

.PHONY: all test clean

test:
	$(COMPILER) $(TEST) $(WARNINGS) $(FLAGS_TEST) $(LD) $(STD) -o loop-test

debug:
	$(COMPILER) $(SRC) $(WARNINGS) $(FLAGS_DEBUG) $(LD) $(STD) -o loop

release:
	$(COMPILER) $(SRC) $(WARNINGS) $(FLAGS_RELEASE) $(LD) $(STD) -o loop

all: debug test

clean:
	rm -f -- loop
	rm -f -- loop-test

install: release
	ln -sf $PWD/loop ~/.local/bin/loop;