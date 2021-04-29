GCC = g++
src = $(wildcard src/*.cpp)
flags = -ggdb -O0 -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17
flags_release =  -O3 -Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor -Werror -std=c++17


debug: 
	$(GCC) $(src) $(flags) -o loop

release:
	$(GCC) $(src) $(flags_release) -o loop

all: debug

clean:
	rm loop