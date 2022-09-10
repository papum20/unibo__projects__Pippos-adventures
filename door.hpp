#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "fixed.hpp"


class Door : public Fixed {
	private:
		int height;
		bool locked;					//se è bloccata (serve chiave)
		bool useable;
		bool boss;						//se è di una boss room
		Coordinate entrancePosition;	//posizione in cui arriva il giocatore dopo aver attraversato la porta

	public:
		Door(Coordinate pos, Coordinate size, Coordinate entrancePosition, bool locked, bool boss = false);
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);

		// SET
		void unlock();						//sblocca (se bloccata)
		void setUseable();
		// GET
		Coordinate getEntrancePosition();	//ritorna la posizione in cui arriva il giocatore dopo aver attraversato la porta
		bool isLocked();					//se è bloccata (e serve chiave)
		bool isUseable();					//se è utilizzabile (per esempio per la porta per il prossimo livello)
		bool isBoss();
};

typedef Door *pDoor;



#endif