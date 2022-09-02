//// MAPPA DI CASELLE CONTENENTI INFORMAZIONI, OGGETTI...

#ifndef MAP_HPP
#define MAP_HPP


#include <iostream>
#include "definitions.hpp"


class Map {
	private:
		Coordinate size;
		int scale_x;							//allargamento orizzontale (in generazione)
		int n_doors_max;						//massimo numero porte (dimensione array)
		int n_doors_sides;						//numero di lati occupati da una porta (attualmente)
		Coordinate door_positions[MAX_SIDES_R];

		pPhysical physical[ROOM_AREA];
		pCharacter characters[ROOM_AREA];
		pDoor doors[MAX_CONNECTED_R];			//array di puntatori a porte (verso stanze collegate)
												//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
		pChest chests[ROOM_AREA];

		pInanimate floorInstance;
		pInanimate wallInstance;

		// FUNZIONI AUSILIARIE
		void addLineToCheck(pPhysical obj[ROOM_AREA], int &found, Coordinate start, Coordinate end);	//funzione ausiliaria per checkRectangle: controlla una linea
		int checkLine_ceil(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);					//funzione ausiliaria per vision: checkLine, implementato con arrotondamento per eccesso
		Coordinate checkLine_floor_next(Coordinate i, Coordinate delta);								//funzione ausiliaria per checkLine: ritorna la prossima casella in una linea (implementato con arrotondamento per difetto), o COORDINATE_ERROR se finisce la linea (incontrando un muro)
		Coordinate checkLine_ceil_next(Coordinate i, Coordinate delta);									//funzione ausiliaria per checkLine: ritorna la prossima casella in una linea (implementato con arrotondamento per eccesso), o COORDINATE_ERROR se finisce la linea (incontrando un muro)

		Coordinate getDoorEntrance(Coordinate door_pos);	//ritorna door.entrancePosition, il punto in cui si ritrova un character che attraversa la porta

		// FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);		//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();						//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE
		void generateDoors(pUnionFind sets);					//genera le porte (generazione stanza)
		// FUNZIONI AUSILIARIE DI GENERAZIONE - SECONDARIE
		void generatePath(Coordinate s, pUnionFind sets);			//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni, ne ritorna il numero
	

	public:
		Map(int scale_x, pInanimate floorInstance, pInanimate wallInstance);
		void destroy();
		void update_all(char input);								//chiama l'update di tutti gli oggetti memorizzati		

		void generate(); 											//genera uno schema randomico per i muri, inserendoli nella map
		void generate_with_doors();									//genera anche le porte
		int shortestPath(Coordinate path[ROOM_AREA], Coordinate A, Coordinate B, pPhysical obj = NULL);
		//ritorna il percorso più breve da A a B, modificando path con i passi da seguire e ritornandone la lunghezza (B incluso, A escluso); ritorna -1 se impossibile;
		//se si vuole il percorso per un oggetto physical, usare il campo obj (altrimenti non serve): permette di calcolare anche il percorso che passi attraverso esso
		int shortestPath_physical(Coordinate path[ROOM_AREA], pPhysical A, pPhysical B, int dist_min = 1, int dist_max = 1);
		//shortestPath per far arrivare un oggetto A a distanza compresa tra dist_min = dist_max (inclusi) da un oggetto B (minimo 1), in linea retta (cioè solo se A e B sono allineati);
		int vision(pPhysical obj[ROOM_AREA], Coordinate source, int range = -1);
		//"visione" a 360 gradi: ritorna tutti gli oggetti visibili (anche passando attraverso physical diversi da wall) in tutte le direzioni a partire da una sorgente source; se <0, il range massimo si considera infinito

		// CHECK
		pPhysical checkPosition(Coordinate pos);					//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		pCharacter checkCharacter(Coordinate pos);					//ritorna l'oggetto (puntatore) character
		pChest checkChest(Coordinate pos);							//ritorna l'oggetto (puntatore) chest
		pDoor checkDoor(Coordinate pos);							//ritorna l'oggetto (puntatore) door
		
		int checkLine(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);	//checkPosition per una linea da start a end (incluso): ritorna tutti gli oggetti trovati in obj e il rispettivo numero
		int checkLine_character(pCharacter obj[ROOM_AREA], Coordinate start, Coordinate end);
		int checkRectangle(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);
		
		bool findLine(pPhysical obj, Coordinate start, Coordinate end);				//cerca obj (puntatore), funziona come checkLine
		bool findRectangle(pPhysical obj, Coordinate start, Coordinate end);		//cerca obj (puntatore), funziona come checkRectangle
		/*
			controlla un rettangolo; i vertici inseriti del rettangolo cambiano l'ordine di ricerca: 1. si cerca sempre da start a end; 2.:
			start.x<=end.x, start.y<=end.y:	verso il basso (riga per riga, da sinistra a destra)
			start.x>end.x, start.y<=end.y:	verso sinistra (colonna per colonna, dall'alto al basso)
			start.x<=end.x, start.y>end.y:	verso destra (colonna per colonna, dal basso all'alto)
			start.x>end.x, start.y>end.y:	verso l'alto (riga per riga, da sinistra a destra)
		*/

		// BOOL
		bool isFreeSpace(Coordinate start, Coordinate end);		//ritona true se il rettangolo è vuoto
		bool isLegalMove(pPhysical obj, Coordinate target);		//ritorna true se obj può occupare, con le sue dimensioni, la cella target

		// GET
		Coordinate getSize();
		int get_n_doors_max();
		pDoor getDoorInIndex(int ind);
		pDoor getDoorInPosition(Coordinate pos);				//door (puntatore) in una posizione

		// EDIT
		void addDoor(int dir, lock_type lt);
		void addCharacter(pCharacter obj);						//aggiunge un character nella sua posizione
		void addChest(pChest obj);								//aggiunge una chest nella sua posizione
		bool move(pPhysical obj, Coordinate target);			//muove un oggetto qualsiasi (non inanimate); ritorna true se ha successo
		void remove(pPhysical obj);								//rimuove un oggetto qualsiasi (non inanimate)
};

typedef Map *pMap;


#include "character.hpp"
#include "chest.hpp"
#include "door.hpp"
#include "floor.hpp"
#include "structures/queue_coordinate.hpp"
#include "physical.hpp"
#include "wall.hpp"


#endif