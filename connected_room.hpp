//// STANZA CON PORTE


#ifndef CONNECTED_ROOM_HPP
#define CONNECTED_ROOM_HPP


#include "door.hpp"
#include "room.hpp"


class ConnectedRoom : public Room {
	private:
		pRoom connected[MAX_CONNECTED_R];	//stanze collegate nella rispettiva direzione con una porta
		int locked_doors;					//numero di porte che richiedono chiave

	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();

		// SET
		void makeConnection(pRoom room, int dir, lock_type lt, bool first = true);	//(overridden) connette questa stanza a room, creando una porta in direzione dir (e la relativa porta in room), con stato bloccato lt; first inizializzato da solo
		bool addLockedDoor();														//aggiunge una porta bloccata, se non superano il massimo (costante); ritorna true se ha successo
		// GET
		pRoom getRoomInPosition(Coordinate pos);				//ritorna il puntatore alla stanza collegata da una porta in posizione pos
		int getLockedDoors();									//ritorna il numero di porte che richiedono chiave (anche se sbloccate)
};

typedef ConnectedRoom *pConnectedRoom;




#endif