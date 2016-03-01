CC = mpicc
CFLAGS = -Wall -02
LIBS = -lm

PROGS = a02

all: $(PROGS)

.c.o:

a02: a02.o
	$(CC -o $@ $(CFLAGS) $^ $(LIBS)
	
clean:
	rm -f $(PROGS) *~*.o*
