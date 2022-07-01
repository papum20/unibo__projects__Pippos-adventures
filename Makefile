main: Bat.o cell.o character.o coordinate.o door.o floor.o inanimate.o level.o main.o physical.o pixel_art.o placeholder.o player.o powerups/health_potion.o room.o timer.o union_find.o wall.o
	g++ Bat.o cell.o character.o coordinate.o door.o floor.o inanimate.o level.o main.o physical.o pixel_art.o placeholder.o player.o powerups/health_potion.o room.o timer.o union_find.o wall.o -lncurses -o main

Bat.o: Bat.cpp Bat.hpp
	g++ -c Bat.cpp
cell.o: cell.cpp cell.hpp
	g++ -c cell.cpp
character.o: character.cpp character.hpp
	g++ -c character.cpp
coordinate.o: coordinate.cpp coordinate.hpp
	g++ -c coordinate.cpp
door.o: door.cpp door.hpp
	g++ -c door.cpp
floor.o: floor.cpp floor.hpp
	g++ -c floor.cpp
inanimate.o: inanimate.cpp inanimate.hpp
	g++ -c inanimate.cpp
level.o: level.cpp level.hpp
	g++ -c level.cpp
main.o: main.cpp main.hpp
	g++ -c main.cpp
physical.o: physical.cpp physical.hpp
	g++ -c physical.cpp
pixel_art.o: pixel_art.cpp pixel_art.hpp
	g++ -c pixel_art.cpp
placeholder.o: placeholder.cpp placeholder.hpp
	g++ -c placeholder.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp
powerups/health_potion.o: powerups/health_potion.cpp powerups/health_potion.hpp
	g++ -c powerups/health_potion.cpp
room.o: room.cpp room.hpp
	g++ -c room.cpp
timer.o: timer.cpp timer.hpp
	g++ -c timer.cpp
union_find.o: union_find.cpp union_find.hpp
	g++ -c union_find.cpp
wall.o: wall.cpp wall.hpp
	g++ -c wall.cpp



clean:
	rm *.o */*.o main main.exe