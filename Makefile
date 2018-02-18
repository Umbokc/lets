BIN=bin/lets
CC=clang++
FL=-g -std=c++11 -stdlib=libc++ -Wall -Wextra -Werror -pedantic -Wc++11-extensions -Wno-everything

SRC=$(shell find . -type f -name '*.cpp')
OBJ=$(patsubst %.cpp, %.o, $(SRC))

all: $(OBJ)
	@mkdir -p bin
	$(CC) -o $(BIN) $(OBJ)

%.o: %.cpp
	$(CC) -c $(FL) $< -lstdc++ -o $@

clean:
	rm -f $(OBJ)
	rm $(BIN)