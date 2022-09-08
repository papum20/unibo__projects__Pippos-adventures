//// STANZA CON PORTE


#ifndef CONNECTED_ROOM_HPP
#define CONNECTED_ROOM_HPP


#include "door.hpp"
#include "room.hpp"


const Coordinate DOOR_SIZE = Coordinate(DOOR_WIDTH, DOOR_DEPTH);


class ConnectedRoom : public Room {
	private:
		int n_doors_max;						//massimo numero porte (dimensione array)
		int locked_doors;						//numero di porte che richiedono chiave
		Coordinate door_positions[MAX_SIDES_R];
		Coordinate door_entrances[MAX_SIDES_R];
		Coordinate door_zones_t[MAX_SIDES_R];
		pRoom connected[MAX_CONNECTED_R];		//stanze collegate nella rispettiva direzione con una porta

		//// FUNZONI AUSILIARIE
		//FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateDoorsPlacehodlers(pUnionFind sets);	//genera dei placeholder per le porte per far si che rimangano connesse al resto della stanza (generazione stanza)
		void generateDoors(bool c);								//genera le porte (generazione stanza)

	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();

		void generate(bool c);

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