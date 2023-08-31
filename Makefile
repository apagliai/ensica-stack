CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: stack_exe

stack_exe: stack.o
	$(CC) $(CFLAGS) $^ -o $@

stack.o: stack.c
	$(CC) $(CFLAGS) -c $^
	
clean: 
	rm -rf *.o *.a
	
distclean: clean
	rm -rf stack_exe
