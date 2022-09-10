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

		//// FUNZONI AUSILIARIE
		int keyChestsNumber();
		//FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateDoorsPlacehodlers(pUnionFind sets);	//genera dei placeholder per le porte per far si che rimangano connesse al resto della stanza (generazione stanza)


	protected:
		pRoom connected[MAX_CONNECTED_R];		//stanze collegate nella rispettiva direzione con una porta
		
		//FUNZIONI AUSILIARIE DI GENERAZIONE
		void generateDoors();								//genera le porte (generazione stanza)

		
	public:
		ConnectedRoom(Coordinate pos);
		void recursiveDestroy();

		void generate();
		virtual void spawn(int level, pCharacter player, bool current = false);

		// SET
		void addDoor(int dir, lock_type lt, bool boss = false);
		bool addLockedDoor();														//aggiunge una porta bloccata, se non superano il massimo (costante); ritorna true se ha successo
		void makeConnection(pRoom room, int dir, lock_type lt, bool first = true);	//(overridden) connette questa stanza a room, creando una porta in direzione dir (e la relativa porta in room), con stato bloccato lt; first inizializzato da solo
		void unlockDoor(pDoor door);												//sblocca porta da entrambi i lati
		// GET
		pRoom getConnectedRoom(pDoor door);						//ritorna il puntatore alla stanza collegata da una porta in posizione pos
		Coordinate getEntrance(pDoor door);						//posizione in cui si entra nell'altra stanza attraversando questa porta
		int getLockedDoors();									//ritorna il numero di porte che richiedono chiave (anche se sbloccate)
};

typedef ConnectedRoom *pConnectedRoom;




#endif