CC = gcc
CFLAGS = -ansi -pedantic -Wall
OBJS = utility.o
COMP = $(CC) $(CFLAGS)

main.exe : main.c $(OBJS)
	$(COMP) $(OBJS) main.c -o main

utility.o : utility.c utility.h
	$(COMP) -c utility.c

debug : main.c
	$(COMP) -g $(OBJS) main.c -o main_debug
	gdb main_debug


run : main.exe
	./main
