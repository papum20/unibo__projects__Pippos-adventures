#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "inanimate.hpp"
#include "room.hpp"


class Door : public Inanimate {
	private:
		Room *room;						//puntatore a stanza a cui collega
		Coordinate entrancePosition;	//posizione in cui arriva il giocatore dopo aver attraversato la porta

		//bool useable;
		//bool player_on;
		

	public:
		Door(Coordinate pos, Room *room, Coordinate entrancePosition);
		//Door(Coordinate pos);
		//void update();

		// SET
		void unconnect();					//room = NULL
		// GET
		Room *getConnected();				//ritorna il puntatore alla stanza collegata
		Coordinate getEntrancePosition();	//ritorna la posizione in cui arriva il giocatore dopo aver attraversato la porta

		//bool canUse();			//se si può cambiare stanza usandola
		//void setPlayerOn(bool p);
};

typedef Door *pDoor;



#endif