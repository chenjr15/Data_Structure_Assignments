objects = main.o Stack.o bintree.o
CC= clang
CFLAGS += --std=c99 -Wall -Werror -Wno-unused
Program = bt
$(Program): $(objects)
		$(CC) $(CFLAGS) -o $(Program) $(objects)
main.o : main.c common.h bintree.h
Stack.o: Stack.h common.h 
bintree.o:bintree.h common.h
.PHONY : clean
clean:
	rm $(Program) $(objects)
