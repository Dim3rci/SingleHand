# Compiler and options
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/program

# Windows compatible: uses 'powershell' or 'dir'
ifeq ($(OS),Windows_NT)
    SOURCES := $(shell powershell -Command "Get-ChildItem -Path $(SRC_DIR) -Recurse -Filter *.cpp | Select-Object -ExpandProperty FullName")
else
    SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
endif

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Default rule
all: $(TARGET)

# Linking objects
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(BUILD_DIR):
	@mkdir -p $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean