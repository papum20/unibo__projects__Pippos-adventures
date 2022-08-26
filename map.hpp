//// //// MAPPA DI CASELLE CONTENENTI INFORMAZIONI, OGGETTI...

#ifndef MAP_HPP
#define MAP_HPP


#include "character.hpp"
#include "definitions.hpp"
#include "door.hpp"
#include "floor.hpp"
#include "wall.hpp"



class Map {
	private:
		Coordinate size;
		int scale_x;
		int n_doors_max;						//massimo numero porte (dimensione array)
		int n_doors_sides;						//numero di lati occupati da una porta (attualmente)
		Coordinate door_positions[MAX_SIDES_R];

		pPhysical physical[ROOM_AREA];
		pCharacter characters[ROOM_AREA];
		pDoor doors[MAX_CONNECTED_R];			//array di puntatori a porte (verso stanze collegate)
												//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		//pItem chest[ROOM_AREA];

		pInanimate floorInstance;
		pInanimate wallInstance;

		// FUNZIONI AUSILIARIE
		Coordinate getDoorEntrance(Coordinate doorCenter);		//ritorna door.entrancePosition, il punto in cui si ritrova un character che attraversa la porta
		// FUNZIONI AUSILIARIE PRINCIPALI (GENERAZIONE)
		void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);		//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();						//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE
		void generateDoors(pUnionFind sets);					//genera le porte (generazione stanza)
		// FUNZIONI AUSILIARIE SECONDARIE (GENERAZIONE)
		void generatePath(Coordinate s, pUnionFind sets);			//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni, ne ritorna il numero
	

	public:
		Map();
		void generate(); 										//genera uno schema randomico per i muri, inserendoli nella map
		void generate_with_doors();

		// CHECK
		pPhysical checkPosition(Coordinate pos);				//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		pCharacter checkCharacter(Coordinate pos);				//ritorna l'oggetto (puntatore) character
		pDoor checkDoor(Coordinate pos);						//ritorna l'oggetto (puntatore) door
		pPhysical checkLine(Coordinate start, Coordinate end);	//checkPosition per una linea da start a end (incluso)
		pCharacter checkLineCharacter(Coordinate start, Coordinate end);

		// GET
		Coordinate getSize();
		int get_n_doors_max();
		pDoor getDoorInIndex(int ind);
		pDoor getDoorInPosition(Coordinate pos);				//door (puntatore) in una posizione

		// EDIT
		void addDoor(int dir, lock_type lt);
		void remove(Coordinate pos);							//rimuove un oggetto (character, item... non inanimate)
};

typedef Map *pMap;


#endif