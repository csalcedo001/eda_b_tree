CXX = g++
CXXFLAGS = -std=c++17 -I include -o $@
TARGET = bin/main
DIRS = bin build

OBJFILES = $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
BINFILES = $(patsubst app/%.cpp, bin/%, $(wildcard app/*.cpp))

.PRECIOUS: $(OBJ)/%.o

all: $(DIRS) $(TARGET)

$(DIRS):
	mkdir $@

bin/%: app/%.cpp # $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^

build/%.o: src/%.cpp include/%.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(DIRS)
