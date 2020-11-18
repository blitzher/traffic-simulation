CC = gcc
CFLAGS = -ansi -pedantic -Wall
COMP = $(CC) $(CFLAGS)

main.exe : main.c
	$(COMP) main.c -o main

run-W : main.exe:
	main.exe

run-M : main.exe:
	./main