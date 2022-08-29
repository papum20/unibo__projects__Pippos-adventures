//// STANZA CON PORTE


#ifndef CONNECTED_ROOM_HPP
#define CONNECTED_ROOM_HPP


#include "door.hpp"
#include "room.hpp"


class ConnectedRoom : public Room {
	private:
		//int n_doors_max;							//massimo numero porte (dimensione array)
		//int n_doors_sides;							//numero di lati occupati da una porta (attualmente)
		//pDoor doors[MAX_CONNECTED_R];				//array di puntatori a porte (verso stanze collegate)
		//											//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		//Coordinate door_positions[MAX_SIDES_R];
		pRoom connected[MAX_CONNECTED_R];	//stanze collegate nella rispettiva direzione con una porta
		int locked_doors;							//numero di porte che richiedono chiave

		// FUNZIONI
		// FUNZIONI AUSILIARIE PRINCIPALI
		//void generateDoors(pUnionFind sets);					//genera le porte (generazione stanza)
		//pDoor findDoor(Coordinate pos);							//ritorna il puntatore a una porta in una posizione, se presente
		//Coordinate getDoorEntrance(Coordinate doorCenter);		//ritorna door.entrancePosition, il punto in cui si ritrova un character che attraversa la porta

	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();
		
		//void generate(); 										//genera uno schema randomico per i muri, inserendoli nell'array grid
		//void update(char input);								//overridden

		// SET
		void makeConnection(pRoom room, int dir, lock_type lt, bool first = true);	//(overridden) connette questa stanza a room, creando una porta in direzione dir (e la relativa porta in room), con stato bloccato lt; first inizializzato da solo
		bool addLockedDoor();														//aggiunge una porta bloccata, se non superano il massimo (costante); ritorna true se ha successo
		// GET
		pRoom getRoomInPosition(Coordinate pos);				//ritorna il puntatore alla stanza collegata da una porta in posizione pos
		//pRoom getRoomInDirection(int dir);						//ritorna il puntatore alla stanza collegata nella direzione

		//pDoor getDoorInPosition(Coordinate pos);
		//pDoor getDoorToRoom(ConnectedRoom *room);				//ritorna il puntatore alla porta che collega alla stanza, se esiste
//		int getSideDoors();				//ritorna il numero di lati occupati da una porta (attualmente)
		int getLockedDoors();									//ritorna il numero di porte che richiedono chiave (anche se sbloccate)
};

typedef ConnectedRoom *pConnectedRoom;




#endif