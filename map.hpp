#ifndef MAP_HPP
#define MAP_HPP


#include "coordinate.hpp"
#include "definitions.hpp"

class Alive;
class Character;
class Chest;
class Door;
class Physical;
class Projectile;


struct Map {
	Coordinate size;
	Physical *physical[ROOM_AREA];
	Character *characters[ROOM_AREA];
	Door *doors[MAX_CONNECTED_R];			//array di puntatori a porte (verso stanze collegate)
											//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
	Chest *chests[ROOM_AREA];
	Projectile *projectiles[ROOM_AREA];
};
typedef Map *pMap;


#endif