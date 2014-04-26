CC=gcc
CFLAGS=-c -O3

all: linear

# debug: CC += -Wall -DDEBUG -g
# debug: spn feistel

# spn stuff

spn: spn.o test.o
	$(CC) $^ -o spn

spn.o: spn.c spn.h
	$(CC) $(CFLAGS) $< -o $@

# linear cryptanalysis stuff

linear: linear.o spn.o
	$(CC) $^ -o linear

linear.o: linearcryptanalysis.c
	$(CC) $(CFLAGS) $< -o $@

# cleaning files

clean:
	rm -rf *.o linear