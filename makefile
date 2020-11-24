CC = gcc
CFLAGS = -ansi -pedantic -Wall
COMP = $(CC) $(CFLAGS)
LIB = libs
TEMP = temp
BIN = bin
SRC = src

# all object files, in the compiled temporary
# directory
OBJS = $(TEMP)/utility.o $(TEMP)/routes.o

$(BIN)/main.exe : directories $(SRC)/main.c $(OBJS) 
	@echo compiling $(BIN)/main.exe...
	@$(COMP) $(OBJS) $(SRC)/main.c -o $(BIN)/main
	@echo Compilation successful

$(TEMP)/%.o : $(LIB)/%.c
	@echo compiling $<...
	@$(COMP) -c $< -o $@

debug : main.c
	$(COMP) -g $(OBJS) main.c -o main_debug
	gdb main_debug

# remove all volatile files
clear :
	@rm -f main
	@rm -f main_debug
	@rm -f *.o
	@rm -f *.exe
	@rm -rf temp
	@rm -rf bin
	@echo cleared temporary files

directories :
	@mkdir -p $(TEMP)
	@mkdir -p $(BIN)

# compile and run main
run : $(BIN)/main.exe
	./main
