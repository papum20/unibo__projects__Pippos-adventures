//// CLASSE CHE SUPPORTA OPERAZIONI SULLA MAPPA/STANZA

#ifndef MAP_HANDLER_HPP
#define MAP_HANDLER_HPP


#include "map.hpp"


class MapHandler {
	private:
		//// FUNZIONI AUSILIARIE
		static pDoor getDoorInPosition(Coordinate pos);							//door (puntatore) in una posizione
		static bool isLegalMove(pMap map, pPhysical obj, Coordinate target);	//ritorna true se obj può occupare, con le sue dimensioni, la cella target
		static bool isFreeSpace(pMap map, Coordinate start, Coordinate end);	//ritona true se il rettangolo è vuot
		//per check
		static void addLineToCheck(pMap map, pPhysical obj[ROOM_AREA], int &found, Coordinate start, Coordinate end);	//funzione ausiliaria per checkRectangle: controlla una linea
		static int checkLine_ceil(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);				//funzione ausiliaria per vision: checkLine, implementato con arrotondamento per eccesso
		static Coordinate checkLine_floor_next(pMap map, Coordinate i, Coordinate delta);								//funzione ausiliaria per checkLine: ritorna la prossima casella in una linea (implementato con arrotondamento per difetto), o COORDINATE_ERROR se finisce la linea (incontrando un muro)
		static Coordinate checkLine_ceil_next(pMap map, Coordinate i, Coordinate delta);								//funzione ausiliaria per checkLine: ritorna la prossima casella in una linea (implementato con arrotondamento per eccesso), o COORDINATE_ERROR se finisce la linea (incontrando un muro)


	public:
		MapHandler();
		static bool move(pMap map, pPhysical obj, Coordinate target);	//muove un oggetto qualsiasi (non inanimate); ritorna true se ha successo
		static void remove(pMap map, pPhysical obj);					//rimuove un oggetto qualsiasi (non inanimate)
		static void addProjectile(pMap map, pProjectile projectile);	//aggiunge un proiettile nella sua posizione

		//// PATH FINDING
		static int shortestPath(pMap map, Coordinate path[ROOM_AREA], Coordinate A, Coordinate B, pPhysical obj = NULL);
		//ritorna il percorso più breve da A a B, modificando path con i passi da seguire e ritornandone la lunghezza (B incluso, A escluso); ritorna -1 se impossibile;
		//se si vuole il percorso per un oggetto physical, usare il campo obj (altrimenti non serve): permette di calcolare anche il percorso che passi attraverso esso
		static int shortestPath_physical(pMap map, Coordinate path[ROOM_AREA], pPhysical A, pPhysical B, int dist_min = 1, int dist_max = 1);
		//shortestPath per far arrivare un oggetto A a distanza compresa tra dist_min = dist_max (inclusi) da un oggetto B (minimo 1), in linea retta (cioè solo se A e B sono allineati);
		static int vision(pMap map, pPhysical obj[ROOM_AREA], Coordinate source, int range = -1);
		//"visione" a 360 gradi: ritorna tutti gli oggetti visibili (anche passando attraverso physical diversi da wall) in tutte le direzioni a partire da una sorgente source; se <0, il range massimo si considera infinito

		//// CHECK
		//singola casella
		static pPhysical checkPosition(pMap map, Coordinate pos);				//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		static pCharacter checkCharacter(pMap map, Coordinate pos);				//ritorna l'oggetto (puntatore) character
		static pChest checkChest(pMap map, Coordinate pos);						//ritorna l'oggetto (puntatore) chest
		static pDoor checkDoor(pMap map, Coordinate pos);						//ritorna l'oggetto (puntatore) door
		//linea/rettangolo
		static int checkLine(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);	//checkPosition per una linea da start a end (incluso): ritorna tutti gli oggetti trovati in obj e il rispettivo numero
		static int checkLine_character(pMap map, pCharacter obj[ROOM_AREA], Coordinate start, Coordinate end);
		static int checkRectangle(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end);
		//find
		static bool findLine(pMap map, pPhysical obj, Coordinate start, Coordinate end);			//cerca obj (puntatore), funziona come checkLine
		static bool findRectangle(pMap map, pPhysical obj, Coordinate start, Coordinate end);		//cerca obj (puntatore), funziona come checkRectangle
		/*
			controlla un rettangolo; i vertici inseriti del rettangolo cambiano l'ordine di ricerca: 1. si cerca sempre da start a end; 2.:
			start.x<=end.x, start.y<=end.y:	verso il basso (riga per riga, da sinistra a destra)
			start.x>end.x, start.y<=end.y:	verso sinistra (colonna per colonna, dall'alto al basso)
			start.x<=end.x, start.y>end.y:	verso destra (colonna per colonna, dal basso all'alto)
			start.x>end.x, start.y>end.y:	verso l'alto (riga per riga, da sinistra a destra)
		*/
};


//#include "character.hpp"
//#include "chest.hpp"

#include "structures/queue_coordinate.hpp"

#include "door.hpp"
#include "floor.hpp"
#include "wall.hpp"
#include "projectile.hpp"


//istanze di muro e pavimento, riutilizzate sempre uguali
const pInanimate FLOOR_INSTANCE = new Floor();
const pInanimate WALL_INSTANCE = new Wall();


#endif