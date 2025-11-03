CXX = clang++-20
CXXFLAGS = -std=c++23 -stdlib=libc++ -O2 -Wall -Iinclude
LDFLAGS = -lvulkan -lglfw -ldl -stdlib=libc++

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
BIN = app

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(BIN)
