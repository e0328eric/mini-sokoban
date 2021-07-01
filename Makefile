CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
LDFLAGS :=

SRC_DIR := ./src
OBJ_DIR := ./obj
SRCS := $(notdir $(wildcard $(SRC_DIR)/*.cc))
OBJS := $(SRCS:.cc=.o)
OBJECTS := $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS := $(OBJECTS:.o=.d)

TARGET := sokoban

all: | mkDirs $(TARGET)

mkDirs:
	mkdir -p $(OBJ_DIR)

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -MD $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)

-include $(DEPS)
