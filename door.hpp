#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "inanimate.hpp"
#include "room.hpp"


class Door : public Inanimate {
	private:
		bool locked;					//se è bloccata (serve chiave)
		Coordinate entrancePosition;	//posizione in cui arriva il giocatore dopo aver attraversato la porta

	public:
		Door(Coordinate pos, Coordinate entrancePosition, bool locked);

		// SET
		void unlock();						//sblocca (se bloccata)
		// GET
		Coordinate getEntrancePosition();	//ritorna la posizione in cui arriva il giocatore dopo aver attraversato la porta
		bool isLocked();					//se è bloccata (e serve chiave)
};

typedef Door *pDoor;



#endif