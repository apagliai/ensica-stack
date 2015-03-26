CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: pagliai_stack

pagliai_stack: pagliai_stack.o
	$(CC) $(CFLAGS) $^ -o $@

pagliai_stack.o: pagliai_stack.c
	$(CC) $(CFLAGS) -c $^
	
clean: 
	rm -rf *.o *.a
	
distclean: clean
	rm -rf pagliai_stack.exe