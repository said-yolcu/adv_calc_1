# Default compiler is gcc
CC = gcc

default: a.out

# Link to create "a.out"
a.out: main.o destructure.o
	$(CC) -o a.out main.o destructure.o 

# Compile and assemble to create main.c
main.o: main.c 
	$(CC) -c main.c

destructure.o: destructure.c 
	$(CC) -c destructure.c

# To clean, type "make clean" to the terminal
clean:
	$(RM) a.out *.o 