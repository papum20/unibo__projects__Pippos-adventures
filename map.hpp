#ifndef MAP_HPP
#define MAP_HPP


#include "coordinate.hpp"
#include "definitions.hpp"

class Character;
class Chest;
class Door;
class Physical;
class Projectile;
typedef Character *pCharacter;
typedef Chest *pChest;
typedef Door *pDoor;
typedef Physical *pPhysical;
typedef Projectile *pProjectile;


struct Map {
	Coordinate size;
	pPhysical physical[ROOM_AREA];
	pCharacter characters[ROOM_AREA];
	pDoor doors[MAX_CONNECTED_R];			//array di puntatori a porte (verso stanze collegate)
											//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
	pChest chests[ROOM_AREA];
	pProjectile projectiles[ROOM_AREA];
};
typedef Map *pMap;


#endif