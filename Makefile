# Project:       ZSP-Project01-2023
# Project Link:  https://github.com/Jekwwer/ZSP-Project02-2023
# Author:        Evgenii Shiliaev
# Date:          12.11.2023

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Isrc/headers
LDFLAGS = -pthread

# Google Test settings
GTEST_DIR = /path/to/gtest
GTEST_INC = -isystem $(GTEST_DIR)/include
GTEST_LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main

# Build settings
SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = $(SRC_DIR)/tests
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTS_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable names
EXEC = $(BIN_DIR)/my_program
TEST_EXEC = $(BIN_DIR)/tests

.PHONY: all clean run tests

all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXEC): $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) $^ -o $@ $(GTEST_LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -c $< -o $@

run: $(EXEC)
	@./$(EXEC)

tests: $(TEST_EXEC)
	@./$(TEST_EXEC)

clean:
	@rm -rf $(BUILD_DIR)

# End of Makefile
