CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = music_system
SOURCES = main.cpp music_system.cpp menu.cpp extended_features.cpp lua_bridge.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp music_system.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET) music_data.txt

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required"

.PHONY: all clean run install
