all : Q6
Q6 : Q6.cpp screen.cpp screen.o
	g++ -o Q6 Q6.cpp screen.o
screen.o: screen.h screen.cpp 
	g++  -o screen.o screen.cpp -c
clean:
	rm*.o
