CXX := g++
CXXFLAGS := --std=c++11 -Wall -Iinclude
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

objects := $(patsubst src/%.cpp, build/%.o, $(shell find src -name "*.cpp" -type f))
main := $(basename $(wildcard *.cpp))

.PHONY: clean all

all: $(main)

clean:
	rm -rf build $(main)

$(objects): build/%.o: src/%.cpp include/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(main): %: %.cpp $(objects)
	$(CXX) $(LDLIBS) $(CXXFLAGS) $^ -o $@
