CC = g++ -fopenmp
CFLAGS= -Wall  $(OPT) -O2  #-g

#gcc -pg -fopenmp
#"-pg" is for "gprof"
# gprof Tree gmon.out > profile_gcc_gravity.txt

CC=icc -openmp -I/usr/include/i386-linux-gnu/
CFLAGS=   -O2 -w1 -Wall $(OPT)


#CFLAGS += -pedantic
#LIBS= -lm

EXEC = All
OBJS = All.o Particle.o Main.o Node.o
INCL = All.h Makefile

SOURCE = All.cpp Particle.cpp Main.cpp Node.cpp $(INCL)

$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)  

All.o: $(SOURCE)
	$(CC) $(CFLAGS) All.cpp -c -o All.o

Main.o: $(SOURCE)
	$(CC) $(CFLAGS) Main.cpp -c -o Main.o

Particle.o: $(SOURCE)
	$(CC) $(CFLAGS) Particle.cpp -c -o Particle.o
	
Node.o: $(SOURCE)
	$(CC) $(CFLAGS) Node.cpp -c -o Node.o
	
clean:
	rm -f $(OBJS) $(EXEC) logfile.log
