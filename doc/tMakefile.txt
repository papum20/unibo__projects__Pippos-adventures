main: main.o level.o room.o character.o player.o enemy.o hud.o inputmanager.o item.o weapon.o powerup.o powerups/health_potion.o
	g++ main.o level.o room.o character.o player.o enemy.o hud.o inputmanager.o item.o weapon.o powerup.o powerups/health_potion.o -lncurses -o main

main.o: main.cpp main.hpp
	g++ -c main.cpp

#MAP
level.o: level.cpp level.hpp
	g++ -c level.cpp
room.o: room.cpp room.hpp
	g++ -c room.cpp

#CHARACTERS
character.o: character.cpp character.hpp
	g++ -c character.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp
enemy.o: enemy.cpp enemy.hpp
	g++ -c enemy.cpp

#HUD/INPUT
hud.o: hud.cpp hud.hpp
	g++ -c hud.cpp
inputmanager.o: inputmanager.cpp inputmanager.hpp
	g++ -c inputmanager.cpp

#ITEMS
item.o: item.cpp item.hpp
	g++ -c item.cpp
weapon.o: weapon.cpp weapon.hpp
	g++ -c weapon.cpp
powerup.o: powerup.cpp powerup.hpp
	g++ -c powerup.cpp
powerups/health_potion.o: powerups/health_potion.cpp powerups/health_potion.hpp
	g++ -c powerups/health_potion.cpp




clean:
	rm *.o */*.o main main.exe