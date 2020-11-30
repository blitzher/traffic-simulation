# setup variables
CC = gcc
CFLAGS = -ansi -pedantic -Wall
COMP = $(CC) $(CFLAGS)
LIB = libs
TEMP = temp
BIN = bin
SRC = src

# all object files, in the compiled 
# temporary directory
OBJS = $(TEMP)/utility.o \
	   $(TEMP)/routes.o \
	   $(TEMP)/colours.o \
	   $(TEMP)/vector.o

% : $(SRC)/%.c $(OBJS)
		
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...

	@$(COMP) $(OBJS) $< -o $(BIN)/$@
	@echo
	@echo Compilation successful

# general rule for compiling any library files
$(TEMP)/%.o : $(LIB)/%.c
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...
	@$(COMP) -c $< -o $@

# don't remove objs when compiling by
# implicit rules
.PRECIOUS : $(OBJS)

# compile with debug flag, and run gdb
debug : $(SRC)/main.c
	@mkdir -p $(TEMP) $(BIN)
	$(COMP) -g $(OBJS) $(SRC)/main.c -o $(BIN)/main_debug
	gdb $(BIN)/main_debug

# remove all items in temporary folders
clear :
	@rm -rf temp
	@rm -rf bin
	@rm -f *.exe
	@rm -f *.o
	@echo cleared temporary files

# clear, then make
clean : clear $(BIN)/main

# compile and run main
run : $(BIN)/main
	@./$(BIN)/main
