all: myShell

CFLAGS=-g -01
myShell: myShell.o myToc.o shellHelper.o 
	cc  myToc.o shellHelper.o myShell.o -o myShell

myShell.o: myToc.h shellHelper.h
	cc -c myShell.c

shellHelper.o: shellHelper.c  shellHelper.h
	cc -c shellHelper.c

myToc.o: myToc.c myToc.h
	cc -c myToc.c

play: myShell
	./myShell

clean:
	rm -f *.o myShell
