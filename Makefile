#------------------------------------------------------------------------------#
# project-pattern.c
#
# Author: Daniel Wojcickoski
# Date: 2021/05/23
# Url: https://github.com/denieu/project-pattern.c
#
# MIT License - Copyright (c) 2021 Daniel Wojcickoski
#------------------------------------------------------------------------------#

#Program version
VERSION=1.2.0
#Compiler
COMPILER=gcc
#Resource compiler
RC_COMPILER=windres
#Executable name
FILENAME=2048C
#Directory of binary files
BIN=./bin
#Directory of .h files
INCLUDE=./includes
#Directory of object files
OBJ=./obj
#Directory of .c files
SRC=./src
#Directory of lib files
LIB=./libs
#Directory of .rc files
RC=./resources

#Compiler flags
FLAGS= -g -Wall
#RC compiler flags
RC_FLAGS=-O coff -o
#Project libs
LIB_FLAGS=-lconio -lpthread
#Libs to link with the compiler
LIBS= -lm -L$(LIB) $(LIB_FLAGS)

#Change .c files to .o files
#Files .c
C_SRC=$(wildcard $(SRC)/*.c)
#Remove prefix and suffix
OBJ_CLEAN=$(notdir $(basename $(C_SRC)))
#Add new prefix and suffix
OBJ_FILES=$(addprefix $(OBJ)/, $(addsuffix .o, $(OBJ_CLEAN)))

#Change .rc files to .res files
#Files .rc
RC_SRC=$(wildcard $(RC)/*.rc)
#Remove prefix and suffix
RC_CLEAN=$(notdir $(basename $(RC_SRC)))
#Add new prefix and suffix
RES_FILES=$(addprefix $(OBJ)/, $(addsuffix .res, $(RC_CLEAN)))

#Commands
.PHONY: all clean

#Make .res .o and final binary
all: compile rc_compile $(FILENAME)

#Make .o files
compile: $(OBJ_FILES)

#Make .res files
rc_compile: $(RES_FILES)

#Make .o file macro
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(COMPILER) $(FLAGS) -c $< -I $(INCLUDE) -o $@

#Make .res file macro
$(OBJ)/%.res: $(RC)/%.rc
	$(RC_COMPILER) $< $(RC_FLAGS) $@

#Make final binary macro
$(FILENAME): $(OBJ_FILES) $(RES_FILES)
	$(COMPILER) $(FLAGS) $(RES_FILES) $(OBJ_FILES) $(LIBS) -o $(BIN)/$@

#Run program
run:
	$(BIN)/$(FILENAME)

#Clean executable and objects
clean:
	rm -f $(OBJ)/*.o
	rm -f $(OBJ)/*.res
	rm -f $(BIN)/$(FILENAME)