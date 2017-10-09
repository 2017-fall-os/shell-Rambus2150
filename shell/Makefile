all: myShell

##CFLAGS=-g -02
myShell: shellHelper.o myShell.o myToc.o 
	cc  myToc.o shellHelper.o myShell.o -o myShell

myShell.o: myToc.h shellHelper.h
	cc -c myShell.c

shellHelper.o: shellHelper.h shellHelper.c 
	cc -c shellHelper.c

myToc.o: myToc.c myToc.h
	cc -c myToc.c

play: myShell
	./myShell

clean:
	rm -f *.o myShell
