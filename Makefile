CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -I/home/liuxia/下载/sdl2/SDL2-devel-2.30.1-VC/SDL2-2.30.1/include
LDFLAGS = -L/home/liuxia/下载/sdl2/SDL2-devel-2.30.1-VC/SDL2-2.30.1/lib
LDLIBS = -lSDL2 -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/main

all: build

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: 
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all build run clean
