main: mainSet.o  Set.o
	g++ $(CFLAGS) -Wall -o main mainSet.o Set.o -lm

mainSet.o: mainSet.C Set.H
	g++ $(CFLAGS) -Wall -o mainSet.o -c mainSet.C

Set.o: Set.C Set.H
	g++ $(CFLAGS) -Wall -o Set.o -c Set.C

