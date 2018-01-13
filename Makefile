CC      = g++
CFLAGS  =
LDFLAGS =
SRCDIR = ./src/

all: Schroedinger.x clean

Schroedinger.x: Schroedinger.o ${SRCDIR}/main.cpp
	$(CC) -o $@ $^ $(LDFLAGS)

Schroedinger.o: ${SRCDIR}/Schroedinger.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean veryclean

clean:
	rm *.o

veryclean: clean
	rm *.x
