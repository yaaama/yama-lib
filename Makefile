##
# yama-lib
#
# @file
# @version 0.1

NAME := yama-lib

# Flags for "make" itself
MAKEFLAGS += --no-print-directory

# Compiler
CC = clang
CFLAGS = -Wall -Wextra -I./src -Wall -std=c11 -pedantic


ifdef DEBUG
CFLAGS += -g -O0 -Wextra -Wunused -Wstrict-prototypes -Wold-style-definition \
-Wshadow -Wvla  -Wconversion
else
CFLAGS += -O3 -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion
endif

ifdef SANITIZE
CFLAGS += -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
LDFLAGS += -fsanitize=address -fsanitize=undefined
endif

##################
# # Sources, etc #
##################

SRC_DIR = src
TESTS_DIR = tests

BUILD_DIR = build
TEST_BIN = $(BUILD_DIR)/test_runner
OBJ_DIR = $(BUILD_DIR)/obj

SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/$(TESTS_DIR)/%.o, $(TEST_FILES))


.PHONY: all test clean

#############
# # Targets #
#############

all: test

test: $(TEST_BIN)
	./$(TEST_BIN) -- -j1 --verbose=5

$(TEST_BIN): $(TEST_OBJ) $(SRC_OBJ)
	@mkdir -p $(@D)
	$(CC) $^ $(LDFLAGS) -lcriterion -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

# end
