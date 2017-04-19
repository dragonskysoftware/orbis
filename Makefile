# Makefile for Orbis
# Compiles code for the game
# Created by Andrew Davis
# Created on 4/9/2017
# All rights reserved

# define the compiler
CXX=clang++

# define the compiler flags
CPPFLAGS=-c -Wall -std=c++14 -Wno-unused-value

# define the library flags
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# define the state-specific library flags
debug: CPPFLAGS += -g

# retrieve the source code
MAIN=$(shell ls src/*.cpp)
TEX=$(shell ls src/texture/*.cpp)
COMP=$(shell ls src/component/*.cpp)
UTIL=$(shell ls src/util/*.cpp)
EXCE=$(shell ls src/except/*.cpp)
DATA=$(shell ls src/data/*.cpp)
EVNT=$(shell ls src/event/*.cpp)
CORE=$(shell ls src/core/*.cpp)
SND=$(shell ls src/audio/*.cpp)
GUI=$(shell ls src/gui/*.cpp)

# compile the source code into a list
SOURCES=$(MAIN) $(TEX) $(COMP) $(UTIL) $(EXCE) $(DATA) $(EVNT) $(CORE) $(SND) $(GUI)

# map the source files to object files
OBJECTS=$(SOURCES:.cpp=.o)

# define the name of the executable
EXECUTABLE=Orbis

# start of build targets

# target to build the entire project without debug symbols
all: $(SOURCES) $(EXECUTABLE)

# target to compile the code
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)
	mkdir bin
	mkdir obj
	mv -f $@ bin/
	mv -f $(OBJECTS) obj/

# target to compile the code with debug symbols
debug: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)
	mkdir bin
	mkdir obj
	mv -f $(EXECUTABLE) bin/
	mv -f $(OBJECTS) obj/

# target to compile the source code into object code
.cpp.o:
	$(CXX) $(CPPFLAGS) $< -o $@

# target to clean the workspace
clean:
	rm -rf bin
	rm -rf obj

# target to install the executable
install:
	cp bin/$(EXECUTABLE) /usr/bin/

# end of Makefile
