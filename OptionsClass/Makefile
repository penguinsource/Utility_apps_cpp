main: mainOpt.o  Opt.o
	g++ $(CFLAGS) -Wall -o main mainOpt.o Opt.o -lm

mainOpt.o: main.C Opt.H
	g++ $(CFLAGS) -Wall -o mainOpt.o -c main.C

Opt.o: Opt.C Opt.H
	g++ $(CFLAGS) -Wall -o Opt.o -c Opt.C
