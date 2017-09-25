all: myShell

CFLAGS=-g -02
myShell: myShell.o myToc.o
	cc myShell.o myToc.o -o myShell

myShell.o: myShell.c myToc.h
	cc -c myShell.c

myToc.o: myToc.c myToc.h
	cc -c myToc.c

play: myShell
	./myShell

clean:
	rm -f *.o myShell
