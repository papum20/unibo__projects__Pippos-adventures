#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "inanimate.hpp"
#include "room.hpp"


class Door : public Inanimate {
	private:
		Room *room;				//puntatore a stanza a cui collega

		//bool useable;
		//bool player_on;
		

	public:
		Door(Coordinate pos, Room *room);
		//Door(Coordinate pos);
		//void update();

		// SET
		void unconnect();		//room = NULL
		// GET
		Room *getConnected();	//ritorna il puntatore alla stanza collegata

		//bool canUse();			//se si può cambiare stanza usandola
		//void setPlayerOn(bool p);
};

typedef Door *pDoor;



#endif