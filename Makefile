CPP     = g++-7
CFLAGS  =
LDFLAGS = 
SRCDIR  = ./src/

GTEST_DIR= ./googletest/googletest
CPPFLAGS = -I$(GTEST_DIR)/include

all: Schroedinger.x clean

Schroedinger.x: Schroedinger.o test.o ${SRCDIR}/main.cpp
	$(CPP) -o $@ $^ $(LDFLAGS) $(CPPFLAGS)

test.o: ${SRCDIR}/test.cpp
	$(CPP) -c $(CPPFLAGS) $<

Schroedinger.o: ${SRCDIR}/Schroedinger.cpp
	$(CPP) -c $(CPPFLAGS) $<

.PHONY: clean veryclean

clean:
	rm *.o

veryclean: clean
	rm *.x
