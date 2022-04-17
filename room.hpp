#ifndef ROOM_H
#define ROOM_H


#include "physical.hpp"
#include "door.hpp"

#define ROOM_WIDTH 320
#define ROOM_HEIGHT 180
#define MAX_CONNECTED_ROOMS 5
#define MAX_SIDES 4




class Room {
	private:
		int width;
		int height;	
		pPhysical grid[ROOM_HEIGHT][ROOM_WIDTH];	//array bidimensionale di oggetti fisici (presenti nelle loro posizioni)
	
		int n_doors_max;							//massimo numero porte (dimensione array)
		int n_doors_sides;							//numero di lati occupati da una porta (attualmente)
		pDoor doors[MAX_CONNECTED_ROOMS];			//array di puntatori a porte (che portano a stanze collegate);
		
	public:
		Room();
		// GENERAZIONE
		void addNthDoor(int n);	//aggiunge una porta nell'n-esima posizione disponibile
		void generateWalls(); 	//genera uno schema randomico per i muri, inserendoli nell'array grid
		// CONTROLLO
		pPhysical checkPosition(int x, int y);
		//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)

		// GET
		pRoom getConnectedRoom(int dir);
		//ritorna il puntatore alla stanza collegata in una data direzione dir
		//0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		int getSideDoors();		//ritorna il numero di lati occupati da una porta (attualmente)
};



typedef Room *pRoom;




#endif