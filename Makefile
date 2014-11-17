all : ppm
ppm : ppm2.c fonction.c fonction.o
	gcc -o ppm ppm2.c fonction.o
fonction.o: fonction.h fonction.c 
	gcc  -o fonction.o fonction.c -c
clean:
	rm*.o


