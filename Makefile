GCC = clang
SRC = $(wildcard src/*.cpp)
FLAGS = -ggdb -O0 -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17
FLAGS_RELEASE =  -O3 -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17
LDFLAGS = -pthread -ldl -lm -lstdc++


debug: 
	$(GCC) $(SRC) $(FLAGS) $(LDFLAGS) -o loop

release:
	$(GCC) $(SRC) $(FLAGS_RELEASE) $(LDFLAGS) -o loop

all: debug

clean:
	rm loop