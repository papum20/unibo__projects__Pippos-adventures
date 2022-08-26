//// //// CELLA DELLA MAPPA

#ifndef MAP_HPP
#define MAP_HPP


#include "character.hpp"
#include "definitions.hpp"
#include "door.hpp"



class Map {
	private:
		pPhysical physical[ROOM_AREA];
		pCharacter character[ROOM_AREA];
		//pItem chest[ROOM_AREA];

};



#endif