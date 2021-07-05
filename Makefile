#DEFAULT SHELL
SHELL   = bash
#COLORS
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32m
ERROR_COLOR=\x1b[31m
WARN_COLOR=\x1b[33m
OK_STRING=$(OK_COLOR)✓$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)⨯$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)problems$(NO_COLOR)
#VARIABLES
CC      = gcc
LD      = gcc
CFLAGS  = -Wall -std=c99 -O2
CFLAGS += `pkg-config --cflags glib-2.0`
#CFLAGS += -Wno-unused-parameter -Wno-unused-function -Wno-unused-result `pkg-config --cflags glib-2.0`
INCLDS  = -I $(INC_DIR) 
LIBS 	= `pkg-config --libs glib-2.0`
SUPP	= --suppressions=/usr/share/glib-2.0/valgrind/glib.supp
#DIRS
BIN_DIR = bin
BLD_DIR = build
DOC_DIR = docs
INC_DIR = includes
SRC_DIR = src
TRASH   = $(BIN_DIR) $(BLD_DIR) 
#
SRC     = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))
DEPS    = $(patsubst $(BLD_DIR)/%.o,$(BLD_DIR)/%.d,$(OBJS))
#
PROGRAM = program
#

vpath %.c $(SRC_DIR)

.DEFAULT_GOAL = build

$(BLD_DIR)/%.d: %.c
	@$(CC) -M $(INCLDS) $(CFLAGS) $< -o $@ $(LIBS)
	
$(BLD_DIR)/%.o: %.c
	@echo -n "Building $(shell basename $@)... "
	@$(CC) -c $(INCLDS)  $(CFLAGS) $< -o $@ $(LIBS)
	@echo -e "$(OK_STRING)"

$(BIN_DIR)/$(PROGRAM): $(DEPS) $(OBJS)
	@echo -n "Compiling... "
	@$(CC) $(INCLDS)  $(CFLAGS) -o $@  -g $(OBJS) $(LIBS)
	@echo -e "$(OK_STRING)"

build: setup $(BIN_DIR)/$(PROGRAM)

program to: build
	@ time ./$(BIN_DIR)/$(PROGRAM) 

debug: CFLAGS = -Wall -Wextra -ansi -pedantic -O0 -g
debug: build
	gdb ./$(BIN_DIR)/$(PROGRAM) 

documentation doc:
	@doxygen $(DOC_DIR)/Doxyfile

setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BLD_DIR)

clean:
	@echo -n "Cleaning... "
	@-rm -rf $(TRASH)
	@echo -e "$(OK_STRING)"

memcheck:
	@G_DEBUG=always-malloc valgrind --leak-check=full $(SUPP) --show-leak-kinds=all -s ./$(BIN_DIR)/$(PROGRAM)