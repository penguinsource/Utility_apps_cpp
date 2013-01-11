hello: mainString.o Opt.o
	g++ -Wall -o hello mainString.o Opt.o

mainString.o: main.C Opt.h
	g++ -Wall -o mainString.o -c main.C

Opt.o: Opt.C Opt.h
	g++ -Wall -c Opt.C
