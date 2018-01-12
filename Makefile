CC      = g++
CFLAGS  =
LDFLAGS =

all: Schroedinger.x clean

Schroedinger.x: Schroedinger.o main.cpp
	$(CC) -o $@ $^ $(LDFLAGS)

Schroedinger.o: Schroedinger.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean veryclean

clean:
	rm *.o

veryclean: clean
	rm *.x
