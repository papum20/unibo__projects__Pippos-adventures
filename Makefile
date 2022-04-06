main: main.o
	g++ main.o -lncurses -o main

main.o: main.cpp
	g++ -c main.cpp
	


clean:
	rm *.o main main.exe