# Compilateur et options
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Dossiers
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/program

# Compatible Windows : utilise 'powershell' ou 'dir'
ifeq ($(OS),Windows_NT)
    SOURCES := $(shell powershell -Command "Get-ChildItem -Path $(SRC_DIR) -Recurse -Filter *.cpp | Select-Object -ExpandProperty FullName")
else
    SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
endif

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Règle par défaut
all: $(TARGET)

# Lien des objets
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Création des dossiers
$(BIN_DIR) $(BUILD_DIR):
	@mkdir -p $@

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean