# Default compiler is gcc
CC = gcc

default: advcalc

# Link to create "advcalc", notice that even though "utilities" is included in 
# "destructure.c", it is linked here, during the creation of executable
advcalc: main.o destructure.o free.o utilities.o variable.o
	$(CC) -o advcalc main.o destructure.o free.o utilities.o variable.o

# Compile and assemble to create main.o
main.o: main.c definitions.h
	$(CC) -c main.c

destructure.o: destructure.c definitions.h
	$(CC) -c destructure.c 

free.o: free.c definitions.h
	$(CC) -c free.c 

utilities.o: utilities.c definitions.h
	$(CC) -c utilities.c 

variable.o: variable.c definitions.h
	$(CC) -c variable.c



# To clean, type "make clean" to the terminal
clean:
	$(RM) a.out *.o advcalc