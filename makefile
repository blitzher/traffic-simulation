CC = gcc
CFLAGS = -ansi -pedantic -Wall
COMP = $(CC) $(CFLAGS)
LIB = libs
TEMP = temp
BIN = bin
SRC = src

# all object files, in the compiled 
# temporary directory
OBJS = $(TEMP)/utility.o $(TEMP)/routes.o

#  compiling src/main.c to bin/main.exe
$(BIN)/main.exe : $(SRC)/main.c $(OBJS) 
		
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $(BIN)/main.exe...

	@$(COMP) $(OBJS) $(SRC)/main.c -o $(BIN)/main
	@echo Compilation successful

$(TEMP)/%.o : $(LIB)/%.c
	
	@mkdir -p $(TEMP) $(BIN)
	@echo Compiling $<...
	@$(COMP) -c $< -o $@

# debug 
debug : $(SRC)/main.c
	# make directories
	@mkdir -p $(TEMP) $(BIN)
	$(COMP) -g $(OBJS) main.c -o $(BIN)/main_debug
	gdb $(BIN)/main_debug

# remove all items in temporary folders
clear :
	@rm -rf temp
	@rm -rf bin
	@echo cleared temporary files

directories : temp bin
	@echo making directories...
	

# compile and run main
run : $(BIN)/main.exe
	@./$(BIN)/main
