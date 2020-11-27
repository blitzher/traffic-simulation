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
	   $(TEMP)/colours.o

# compiling src/car.c to bin/car
$(BIN)/car : $(SRC)/car.c $(OBJS) 
		
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $(BIN)/car.exe...

	@$(COMP) $(OBJS) $(SRC)/car.c -o $(BIN)/car
	@echo
	@echo Compilation successful

# general rule for compiling any library files
$(TEMP)/%.o : $(LIB)/%.c
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...
	@$(COMP) -c $< -o $@

# compile with debug flag, and run gdb
debug : $(SRC)/car.c
	@mkdir -p $(TEMP) $(BIN)
	$(COMP) -g $(OBJS) $(SRC)/car.c -o $(BIN)/car_debug
	gdb $(BIN)/car_debug

# remove all items in temporary folders
clear :
	@rm -rf temp
	@rm -rf bin
	@rm -f *.exe
	@rm -f *.o
	@echo cleared temporary files

# clear, then make
clean : clear $(BIN)/car

# compile and run car
run : $(BIN)/car
	@./$(BIN)/car
