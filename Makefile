GCC = clang
TEST = $(wildcard test/*.cpp)
SRC = $(wildcard src/*.cpp)
FLAGS = -ggdb -O0 -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17
FLAGS_RELEASE = -O3 -std=c++17
FLAGS_TEST = -fexceptions  -frtti -std=c++17
LDFLAGS = -pthread -ldl -lm -lstdc++


test:
	$(GCC) $(TEST) $(FLAGS_TEST) $(LDFLAGS) -o loop-test

debug: 
	$(GCC) $(SRC) $(FLAGS) $(LDFLAGS) -o loop

release:
	$(GCC) $(SRC) $(FLAGS_RELEASE) $(LDFLAGS) -o loop

all: debug

clean:
	rm loop

.PHONY: all test 