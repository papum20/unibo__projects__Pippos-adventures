#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "physical.hpp"
#include "room.hpp"


class Door : public Physical {
	private:
		Room *room;		//puntatore a stanza a cui collega
	public:
		Door(int x, int y, Room *room);

		// GET
		Room *getConnected();				//ritorna il puntatore alla stanza collegata
};
typedef Door *pDoor;




#endif