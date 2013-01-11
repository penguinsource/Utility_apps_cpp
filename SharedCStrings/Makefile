main: mainString.o  String.o
	g++ $(CFLAGS) -Wall -o main mainString.o String.o

mainString.o: main.C String.H
	g++ $(CFLAGS) -Wall -o mainString.o -c mainString.C

String.o: String.C String.H
	g++ $(CFLAGS) -Wall -o String.o -c String.C

