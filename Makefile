CXX := g++
CXXFLAGS := --std=c++11 -Wall -Iinclude
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

objects := $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
main := $(basename $(wildcard *.cpp))

.PHONY: clean all

all: $(main)

clean:
	rm -rf build $(main)

build:
	mkdir build

build/%.o: src/%.cpp include/%.hpp build
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(main): %: %.cpp $(objects)
	$(CXX) $(LDLIBS) $(CXXFLAGS) $^ -o $@
