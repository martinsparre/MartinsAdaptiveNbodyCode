CC = g++
#gcc -pg -fopenmp
CFLAGS= -Wall  $(OPT) -O2 #-g
#"-pg" is for "gprof"
# gprof Tree gmon.out > profile_gcc_gravity.txt


#CC=icc #-openmp
#CFLAGS= -g -O2 -marchcore2 -w1 $(OPT)
#-marchcore2: optimized for Intel Dual Core

#CFLAGS += -pedantic

#LIBS= -lm

EXEC = All
OBJS = All.o Particle.o Main.o Node.o
INCL = All.h Makefile

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)  

$(OBJS): $(INCL)

clean:
	rm -f $(OBJS) $(EXEC) logfile.log
