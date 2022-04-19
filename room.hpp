#ifndef ROOM_H
#define ROOM_H


#include "level.hpp"
#include "physical.hpp"
#include "door.hpp"

#define ROOM_WIDTH 320		//larghezza stanza
#define ROOM_HEIGHT 180		//altezza stanza
#define MAX_CONNECTED_R 5	//massimo numero di stanze collegate a ognuna
#define MAX_SIDES_R 4		//massimo numero di stanze (normali) collegate sui lati




class Room {
	private:
		short x, y;									//coordinate rispetto alla prima stanza del livello

		short width;
		short height;	
		pPhysical grid[ROOM_HEIGHT][ROOM_WIDTH];	//array bidimensionale di oggetti fisici (presenti nelle loro posizioni)
	
		short n_doors_max;							//massimo numero porte (dimensione array)
		short n_doors_sides;						//numero di lati occupati da una porta (attualmente)
		pDoor doors[MAX_CONNECTED_R];				//array di puntatori a porte (che portano a stanze collegate);
		
	public:
		Room(short x, short y);
		// GENERAZIONE
		void addNthDoor(short n);	//aggiunge una porta nell'n-esima posizione disponibile
		void generateWalls(); 		//genera uno schema randomico per i muri, inserendoli nell'array grid
		// CONTROLLO
		pPhysical checkPosition(short x, short y);	//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)

		// SET
		void makeConnection(pRoom room, short dir);	//connects this room to "room" in direction dir (relative to this)
		// GET
		short getX();
		short getY();
		pRoom getConnectedRoom(short dir);	//ritorna il puntatore alla stanza collegata in una data direzione dir
											//0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		short getSideDoors();				//ritorna il numero di lati occupati da una porta (attualmente)
};



typedef Room *pRoom;




#endif