//// STANZA CON PORTE


#ifndef CONNECTED_ROOM_HPP
#define CONNECTED_ROOM_HPP


#include "door.hpp"
#include "room.hpp"


class ConnectedRoom : public Room {
	private:
		int n_doors_max;						//massimo numero porte (dimensione array)
		int n_doors_sides;						//numero di lati occupati da una porta (attualmente)
		int locked_doors;						//numero di porte che richiedono chiave
		Coordinate door_positions[MAX_SIDES_R];
		pRoom connected[MAX_CONNECTED_R];		//stanze collegate nella rispettiva direzione con una porta

		//// FUNZONI AUSILIARIE
		Coordinate calcDoorEntrance(Coordinate door_pos);	//calcola door.entrancePosition, il punto in cui si ritrova un character che attraversa la porta
		//FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateDoors(pUnionFind sets);	//genera le porte (generazione stanza)

	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();

		void generate();

		// SET
		void makeConnection(pRoom room, int dir, lock_type lt, bool first = true);	//(overridden) connette questa stanza a room, creando una porta in direzione dir (e la relativa porta in room), con stato bloccato lt; first inizializzato da solo
		void addDoor(int dir, lock_type lt);
		bool addLockedDoor();														//aggiunge una porta bloccata, se non superano il massimo (costante); ritorna true se ha successo
		// GET
		pRoom getRoomInPosition(Coordinate pos);				//ritorna il puntatore alla stanza collegata da una porta in posizione pos
		//pDoor getDoorInPosition(Coordinate pos) 
		int getLockedDoors();									//ritorna il numero di porte che richiedono chiave (anche se sbloccate)
};

typedef ConnectedRoom *pConnectedRoom;




#endif