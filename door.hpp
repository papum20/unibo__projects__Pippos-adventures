#ifndef DOOR_HPP
#define DOOR_HPP

#include "physical.hpp"
#include "room.hpp"


class Door : public Physical {
	private:
		int xPos;
		int yPos;
		pRoom room;		//puntatore a stanza a cui collega
	public:
		Door(int x, int y, pRoom room);

		// GET
		pRoom getConnected();	//ritorna il puntatore alla stanza collegata
};


typedef Door *pDoor;


#endif