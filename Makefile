# Project: 		ZSP-Homework01-2023
# Project Link: https://github.com/Jekwwer/ZSP-Project01-2023
# Author:  		Evgenii Shiliaev
# Date:    		29.10.2023

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Executable name
TARGET = zsp01

# Target executable for tests
TEST_TARGET = tests

# Source files
SRC = zsp01_functions.cpp main.cpp
TESTS = zsp01_tests.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST_TARGET) : $(TESTS)
	$(CXX) $(CXXFLAGS) -pthread zsp01_functions.o $(TESTS) -lgtest -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f $(TEST_TARGET) *.o

.PHONY: clean

# End of Makefile