CC = gcc
CFLAGS = -ansi -pedantic -Wall
OBJS = utility.o routes.o
COMP = $(CC) $(CFLAGS)

main.exe : main.c $(OBJS)
	$(COMP) $(OBJS) main.c -o main

utility.o : utility.c utility.h
	$(COMP) -c utility.c

routes.o : routes.c routes.h
	$(COMP) -c routes.c

debug : main.c
	$(COMP) -g $(OBJS) main.c -o main_debug
	gdb main_debug

# remove all volatile files
clear :
	@rm -f main
	@rm -f main_debug
	@rm -f *.o
	@rm -f *.exe
	@echo cleared files

# compile and run main
run : main.exe
	./main
