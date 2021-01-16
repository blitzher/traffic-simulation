# setup variables
CC = gcc
CFLAGS = -ansi -pedantic -Wall
COMP = $(CC) $(CFLAGS)
LIB = include
TEMP = lib
BIN = bin
SRC = src

# all object files, in the compiled 
# temporary directory
OBJS = $(TEMP)/utility.o \
	   $(TEMP)/routes.o \
	   $(TEMP)/colours.o \
	   $(TEMP)/vector.o \
	   $(TEMP)/simulation.o

$(BIN)/%.exe : $(SRC)/%.c $(OBJS)
		
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...

	@$(COMP) $(OBJS) $< -o $@
	@echo
	@echo Compilation successful

# general rule for compiling any library files
$(TEMP)/%.o : $(LIB)/%.c $(LIB)/%.h
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...
	@$(COMP) -c $< -o $@

# don't remove objs when compiling by
# implicit rules
.PRECIOUS : $(OBJS)

# compile with debug flag, and run gdb
debug : $(SRC)/main.c $(OBJS)
	$(COMP) -g $(OBJS) $(SRC)/main.c -o $(BIN)/main_debug
	gdb $(BIN)/main_debug

# remove all items in temporary folders
clear :
	@rm -rf $(TEMP)
	@rm -rf $(BIN)
	@rm -f *.exe
	@rm -f *.o
	@rm -f .output
	@rm -f .visuals
	@echo cleared temporary files

# clear, then make
clean : clear $(BIN)/main.exe

# compile and run main
run : $(BIN)/main.exe
	@./$(BIN)/main.exe
	
