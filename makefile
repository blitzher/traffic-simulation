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
debug : $(SRC)/car.c $(OBJS)
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
clean : clear $(BIN)/car.exe

# compile and run main
run : $(BIN)/car.exe
	@./$(BIN)/car.exe
