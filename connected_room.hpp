#ifndef CONNECTED_ROOM_HPP
#define CONNECTED_ROOM_HPP


#define MAX_CONNECTED_R 5					//massimo numero di stanze collegate a ognuna
#define MAX_SIDES_R 4						//massimo numero di stanze (normali) collegate sui lati


#include "door.hpp"
#include "room.hpp"


class ConnectedRoom : public Room {
	private:
		int n_doors_max;							//massimo numero porte (dimensione array)
		int n_doors_sides;							//numero di lati occupati da una porta (attualmente)
		pDoor doors[MAX_CONNECTED_R];				//array di puntatori a porte (che portano a stanze collegate;
													//disposte in direzioni 0..3=su..sinistra, da 4+ stanze interne
		Coordinate door_positions[MAX_SIDES_R];
		ConnectedRoom *connected[MAX_CONNECTED_R];	//stanze collegate nella rispettiva direzione con una porta

		// FUNZIONI
		// FUNZIONI AUSILIARIE PRINCIPALI
		void generateDoors(pUnionFind sets);
		pDoor findDoor(Coordinate pos);

	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();
		
		void generate(); 									//genera uno schema randomico per i muri, inserendoli nell'array grid
		void update();										//overridden

		// SET
		void makeConnection(ConnectedRoom *room, int dir);	//connects this room to "room" in direction dir (relative to this)
		// GET
		ConnectedRoom *getRoomInPosition(Coordinate pos);	//ritorna il puntatore alla stanza collegata da una porta
		ConnectedRoom *getRoomInDirection(int dir);			//ritorna il puntatore alla stanza collegata nella direzione
															//0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		pDoor getDoorInPosition(Coordinate pos);
		pDoor getDoorToRoom(ConnectedRoom *room);			//ritorna il puntatore alla porta che collega alla stanza, se esistea
//		int getSideDoors();				//ritorna il numero di lati occupati da una porta (attualmente)
};

typedef ConnectedRoom *pConnectedRoom;




#endif