#compiler and flags 
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra 

#Directories
SRC_DIR = src
BIN_DIR = bin
#SAVE_DIR = save_files

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/save_utils.c $(SRC_DIR)/display_utils.c 
EXEC = $(BIN_DIR)/editor

#default rule: build the whole project
all: $(EXEC)

$(EXEC) : $(SOURCES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

#clean rule: remove compiled files
clean: 
	rm -rf $(BIN_DIR)
