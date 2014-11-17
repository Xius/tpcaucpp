all : ppm
ppm : ppm2.cpp fonction.cpp fonction.o
	g++ -o ppm ppm2.cpp fonction.o
fonction.o: fonction.h fonction.cpp 
	g++  -o fonction.o fonction.cpp -c
clean:
	rm*.o


