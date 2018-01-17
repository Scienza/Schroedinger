CC      = g++-7
CFLAGS  =
LDFLAGS =
SRCDIR = ./src/

all: Schroedinger.x clean

Schroedinger.x: Schroedinger.o test.o ${SRCDIR}/main.cpp
	$(CC) -o $@ $^ $(LDFLAGS)

test.o: ${SRCDIR}/test.cpp
	$(CC) -c $(CFLAGS) $<

Schroedinger.o: ${SRCDIR}/Schroedinger.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean veryclean

clean:
	rm *.o

veryclean: clean
	rm *.x
