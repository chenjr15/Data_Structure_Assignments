objects = main.o LGraph.o Queue.o
#CC= gcc
CFLAGS += -g  --std=c99 -Wall -Wno-unused
CFLAGS += -DCOLORTEXT

Program = GraphTest
$(Program): $(objects)
		$(CC) $(CFLAGS) -o $(Program) $(objects)
main.o : main.c  LGraph.h common.h 
LGraph.o : LGraph.h common.h 
Queue.o: common.h Queue.h
.PHONY : cleans
clean:
	rm $(Program) $(objects)
