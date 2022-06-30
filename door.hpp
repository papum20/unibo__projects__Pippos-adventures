#ifndef DOOR_HPP
#define DOOR_HPP

#include "physical.hpp"
#include "room.hpp"
#include "coordinate.hpp"


class Door : public Physical {
	private:
		pRoom room;		//puntatore a stanza a cui collega
	public:
		Door(int x, int y, pRoom room);

		// GET
		pRoom getConnected();				//ritorna il puntatore alla stanza collegata
};


typedef Door *pDoor;


#endif