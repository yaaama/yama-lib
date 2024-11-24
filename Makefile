##
# yama-lib
#
# @file
# @version 0.1

# Compiler
CC = clang

NAME := yama-lib
# Commands:
RM := rm -f
# Flags for "make" itself
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)


##################
# # Sources, etc #
##################

SRCDIR = src
BUILDDIR = build
TESTDIR = tests

# Source files excluding main.c for tests
SRCS := $(filter-out $(SRCDIR)/main.c, $(wildcard $(SRCDIR)/*.c))
# All source files for building the main executable
ALL_SRCS = $(wildcard $(SRCDIR)/*.c)

# Object files (for main)
OBJS = $(addprefix $(BUILDDIR)/,$(notdir $(ALL_SRCS:.c=.o)))
# Object files excluding main.c for testing purposes
TEST_OBJS = $(addprefix $(BUILDDIR)/,$(notdir $(SRCS:.c=.o)))

# Test source files
TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
# Test object files
TEST_OBJ_FILES = $(addprefix $(BUILDDIR)/,$(notdir $(TEST_SRCS:.c=.o)))


# Compiler options
CFLAGS := -Wall -ggdb -O0 -std=c11 -Wextra -Wunused -pedantic
CFLAGS += -MMD -MP -Wstrict-prototypes -Wold-style-definition
CFLAGS += -Wshadow -Wvla -Wno-unused-parameter -Wno-unused-function -Wconversion -Wno-sign-conversion
CFLAGS_ASAN := -fsanitize=address -fsanitize=undefined
CFLAGS += -fsanitize=address -fsanitize=undefined

#############
# # Targets #
#############

# Default target to build only the main library
all: build/yama-lib

# Build the main library
build/yama-lib: $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_ASAN) -o $@ $^
	$(info CREATED $(NAME))

# Compile source files into object files (includes main.c)
build/%.o: src/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

# Test target: builds and runs the tests without main.c
tests: build/tests-runner
	$(info RUNNING TESTS)
	./build/tests-runner

# Test runner executable, linking library object files (excluding main.c) and test object files
build/tests-runner: $(TEST_OBJS) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lcriterion
	$(info CREATED test runner)

# Compile test files into object files
build/%.o: tests/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED test object $@)

# Cleans build directory
clean:
	$(RM) $(OBJS) $(TEST_OBJ_FILES) build/tests-runner build/yama-lib

fclean: clean

.PHONY: clean fclean
.SILENT:


# end
