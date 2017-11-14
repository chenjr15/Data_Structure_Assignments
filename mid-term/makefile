CC = clang
Program = mid-term.linux
objects = main.o Queue.o bintree.o Stack.o
CFLAGS += --std=c99 -Wall -Werror -Wno-unused
$(Program): $(objects)
		$(CC) $(CFLAGS) -o $(Program) $(objects)
main.o : main.c common.h bintree.h Queue.h Stack.h
Queue.o: Queue.h common.h 
bintree.o:bintree.h common.h Queue.h
Stack.o:common.h  Stack.h
.PHONY : clean
clean:
	rm $(Program) $(objects)