# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)Sokoban.hpp \
       $(SRC)SokobanConstants.hpp \
       $(SRC)SokobanTileGrid.hpp \
       $(SRC)SokobanPlayer.hpp \
       $(SRC)SokobanScore.hpp \
       $(SRC)SokobanElapsedTime.hpp \
       $(SRC)InvalidCoordinateException.hpp

# Object files that are not in the static library
OBJECTS = $(SRC)main.o

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)Sokoban.o \
                     $(SRC)SokobanTileGrid.o \
                     $(SRC)SokobanPlayer.o \
                     $(SRC)SokobanScore.o \
                     $(SRC)SokobanElapsedTime.o \
                     $(SRC)InvalidCoordinateException.o

# Static library
STATIC_LIB = Sokoban.a

# Program
PROGRAM = Sokoban

# The test object files
TEST_OBJECTS = $(SRC)test.o

# The test program
TEST_PROGRAM = test

.PHONY: all clean lint

# Default target to build both the test program and main program
all: $(TEST_PROGRAM) $(PROGRAM)

# Compile C++ source files into object files
$(SRC)%.o: $(SRC)%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $< -o $@

# Link object files to create the main program
$(PROGRAM): $(OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

# Create a static library from object files
$(STATIC_LIB): $(STATIC_LIB_OBJECTS)
	ar rcs $@ $^

# Link test object files to create the test program
$(TEST_PROGRAM): $(TEST_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

# Run unit tests using the test program
boost: $(TEST_PROGRAM)
	./$<

# Run the main program with a level file
run: $(PROGRAM)
	./$< assets/level/level7.lvl

# Clean up generated files
clean:
	rm -f $(SRC)*.o $(PROGRAM) $(STATIC_LIB) $(TEST_PROGRAM)

# Lint source files
lint:
	cpplint $(SRC)*.hpp $(SRC)*.cpp
