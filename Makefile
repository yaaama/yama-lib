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

# Source files
SRCS = $(wildcard src/*.c)
# Object files
OBJS = $(addprefix build/,$(notdir $(SRCS:.c=.o)))

# Compiler options
CFLAGS := -Wall -g3 -O0 -std=c11 -Wextra -Wunused -pedantic
CFLAGS += -MMD -MP -Wstrict-prototypes -Wold-style-definition
CFLAGS += -Wshadow -Wvla -Wno-unused-parameter -Wno-unused-function -Wconversion -Wno-sign-conversion -fsanitize=address -fsanitize=undefined

#############
# # Targets #
#############


# default target
all: build/yama-lib

build/yama-lib: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	$(info CREATED $(NAME))

build/%.o: src/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

# Cleans build directory
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY: clean fclean
.SILENT:


# end


# end
