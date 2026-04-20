# compiler used
CXX = g++

# Flags
# use C++17 standard
# Wall - show all warnings
# Wextra - show extra warnings. These catch bugs before they become problems
CXXFLAGS = -std=c++17 -Wall -Wextra

# File paths
SRC      = src/LRUCache.cpp src/main.cpp
TEST_SRC = src/LRUCache.cpp tests/test_cache.cpp

# Output binaries
TARGET      = cache
TEST_TARGET = tests/run_tests

# ─────────────────────────────────
# Default — build the simulator
# ─────────────────────────────────
all: $(TARGET)
# all is the default rule — 
# what runs when you just type make. It builds the simulator.


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "✓ Build successful — run with ./cache"

# ─────────────────────────────────
# Build and run tests
# ─────────────────────────────────
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

# ─────────────────────────────────
# Remove compiled files
# Deletes compiled binaries.
# Useful before pushing to git or starting fresh.
# ─────────────────────────────────
clean:
	rm -f $(TARGET) $(TEST_TARGET)
	@echo "✓ Cleaned build files"