main: a.o Bat.o character.o door.o level.o main.o physical.o player.o powerups/health_potion.o room.o wall.o
	g++ a.o Bat.o character.o door.o level.o main.o physical.o player.o powerups/health_potion.o room.o wall.o -lncurses -o main

a.o: a.cpp
	g++ -c a.cpp
Bat.o: Bat.cpp Bat.hpp
	g++ -c Bat.cpp
character.o: character.cpp character.hpp
	g++ -c character.cpp
door.o: door.cpp door.hpp
	g++ -c door.cpp
level.o: level.cpp level.hpp
	g++ -c level.cpp
main.o: main.cpp main.hpp
	g++ -c main.cpp
physical.o: physical.cpp physical.hpp
	g++ -c physical.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp
powerups/health_potion.o: powerups/health_potion.cpp powerups/health_potion.hpp
	g++ -c powerups/health_potion.cpp
room.o: room.cpp room.hpp
	g++ -c room.cpp
wall.o: wall.cpp wall.hpp
	g++ -c wall.cpp



clean:
	rm *.o */*.o main main.exe