CXX = g++

default: bitDriver

bitDriver: bitDriver.o BitArray.o
	$(CXX) -Wall  -o bitDriver bitDriver.o BitArray.o

bitDriver.o: bitDriver.cpp
	$(CXX) -Wall -c  bitDriver.cpp
BitArray.o: BitArray.cpp BitArray.h
	$(CXX) -Wall -c  BitArray.cpp

clean:
	rm bitDriver *.o
