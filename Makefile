CPP     = g++-7
CFLAGS  =
LDFLAGS = -lgtest -lpthread
SRCDIR  = ./src/
OBJ_DIR= ./obj
CXXFLAGS = -g -Wall
GTEST_DIR= ./googletest/googletest
CPPFLAGS = -I$(GTEST_DIR)/include -L$(GTEST_DIR)/mybuild

all: Schroedinger.x clean

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS = -g -Wall -Wextra -pthread 

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
   	            -o $@ $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
   	            -o $@ $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

Schroedinger.x: Schroedinger.o test.o ${SRCDIR}/main.cpp
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

test.o: ${SRCDIR}/test.cpp 
	$(CPP) -c $(CFLAGS) $<

Schroedinger.o: ${SRCDIR}/Schroedinger.cpp
	$(CPP) -c $(CFLAGS) $<

.PHONY: clean veryclean

clean:
	rm *.o

veryclean: clean
	rm *.x
