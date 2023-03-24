# Default compiler is gcc
CC = gcc

default: a.out

# Link to create "a.out", notice that even though "utilities" is included in 
# "destructure.c", it is linked here, during the creation of executable
a.out: main.o destructure.o free.o utilities.o
	$(CC) -o a.out main.o destructure.o free.o utilities.o

# Compile and assemble to create main.c
main.o: main.c 
	$(CC) -c main.c

destructure.o: destructure.c 
	$(CC) -c destructure.c 

free.o: free.c 
	$(CC) -c free.c 

utilities.o: utilities.c 
	$(CC) -c utilities.c 



# To clean, type "make clean" to the terminal
clean:
	$(RM) a.out *.o 