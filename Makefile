BIN=bin/lets
TEST_BIN=bin/tests
CXX ?= clang++
CXX_AVAILABLE := $(shell command -v $(CXX) >/dev/null 2>&1 && echo yes || echo no)
ifeq ($(CXX_AVAILABLE),no)
CXX := g++
endif

CXXFLAGS = -g -std=c++11
ifeq ($(CXX),clang++)
CXXFLAGS += -Wall -Wextra -Werror -pedantic -stdlib=libc++ -Wc++11-extensions -Wno-everything
else
CXXFLAGS += -Wall -Wextra -pedantic
endif

SRC=$(shell find . -type f -name '*.cpp' ! -path './tests/*')
OBJ=$(patsubst %.cpp, %.o, $(SRC))
TEST_SRC=$(shell find tests -type f -name '*.test.cpp')

.PHONY: all clean test

all: $(OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(TEST_BIN): $(TEST_SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -I. $(TEST_SRC) -o $(TEST_BIN)

test: $(TEST_BIN)
	$(TEST_BIN)

clean:
	rm -f $(OBJ)
	rm -f $(BIN) $(TEST_BIN)
