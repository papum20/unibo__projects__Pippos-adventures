#ifndef ROOM_H
#define ROOM_H


#include "physical.hpp"

#define ROOM_WIDTH 320
#define ROOM_HEIGHT 180
#define MAX_CONNECTED_ROOMS 5




class Room {
	private:
		pPhysical grid[ROOM_HEIGHT][ROOM_WIDTH];	//array bidimensionale di oggetti fisici (presenti nelle loro posizioni)
		Room *connected[MAX_CONNECTED_ROOMS];		//array di puntatori a stanze collegate (con una porta)
	public:
		Room();
		// CONTROLLO
		pPhysical checkPosition(int x, int y);
		//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
};



typedef Room *pRoom;




#endif