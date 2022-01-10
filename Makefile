CC = g++
COMPILER_FLAGS = -std=c++11 -Wall -pedantic -O0 -g
LINKER_FLAGS = -lsdl2 -lsdl2_image -lsdl2_ttf
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build/debug
OBJ_NAME = main
SRC_DIR = src

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

