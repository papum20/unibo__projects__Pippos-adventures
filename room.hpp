#ifndef ROOM_HPP
#define ROOM_HPP


#include "coordinate.hpp"
#include "definitions.hpp"


//per ogni indice i, DIR_CHANCES[i] è la probabilità di generare i percorsi a partire da un punto (nella generazione della stanza);
//la prima posizione indica la probabilità di generare in 0 nuove direzioni (cioè di fermarsi)
const int DIR_CHANCES[DIRECTIONS_N + 1] = {5, 20, 10, 3, 1};
//COSTANTI PER MAKECONNECTION(): PER QUALI PORTE BLOCCARE CON CHIAVE
#define LOCKED_DOORS_MAX 1		//massimo numero di porte bloccate da chiave in una stanza
typedef char lock_type;
#define LOCK_TYPES_N 4			//numero di stati
#define LOCK_NONE	(lock_type)0
#define LOCK_OWN	(lock_type)1
#define LOCK_OTHER	(lock_type)2
#define LOCK_BOTH	(lock_type)3


#include "map_handler.hpp"
#include "structures/union_find.hpp"

#include "enemy.hpp"




class Room {
	private:
		Coordinate pos;											//coordinate rispetto alla prima stanza del livello

		//// FUNZIONI AUSILIARIE
		int getFreeCells(s_coord available[], Coordinate size);		//modifica l'array con le celle disponibili per lo spawn di qualcosa di dimensione size e ne ritorna il numero
		// ADD
		void addCharacter(pCharacter obj);							//aggiunge un character nella sua posizione
		void addChest(pChest obj);									//aggiunge una chest nella sua posizione
		// FUNZIONI AUSILIARIE DI GENERAZIONE - SECONDARIE
		void generatePath(Coordinate s, pUnionFind sets);			//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni, ne ritorna il numero
	protected:
		Coordinate size;		//dimensioni effettive
		Coordinate size_t;		//dimensioni senza l'allargamento scale_x
		int scale_x;											//ridimensionamento orizzontale (in generazione)
		pMap map;
		
	// FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);		//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();						//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE


	public:
		Room(Coordinate pos);
		void recursiveDestroy();								//elimina tutti i puntatori contenuti nella stanza, agendo poi ricorsivamente sulle stanze collegate
		void update(int input);									//da richiamare a ogni frame; chiama l'update di ogni elemento nella stanza
		
		virtual void generate(); 								//genera uno schema randomico per i muri, inserendoli nell'array map
		
		void spawnEnemy(pEnemy enemy);							//spawna un nemico
		void spawnChest(pChest chest);							//spawna una chest
		// DISEGNO
		void draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center);	//riempie l'array con le informazioni per stampare a schermo, con opportune modifiche di prospettiva e altro;
																									//inquadra solo un rettangolo con le dimensioni dei parametri intorno al giocatore

		// GET
		Coordinate getPos();
		Coordinate getSize();
		//void getMap(pPhysical map[], Coordinate &size);			//modifica mappa, ritorna dimensioni
		virtual Room *getRoomInPosition(Coordinate pos);		//ritorna il puntatore alla stanza collegata da una porta in posizione pos

		// SET
		virtual void makeConnection(Room *room, int dir, lock_type lt, bool first = true);	//collega l'altra stanza a questa (se è connectedRoom), con stato bloccato lt; first inizializzato da solo
		bool setPosition_strong(pPhysical obj, Coordinate pos);								//posiziona obj in pos e, se lo spazio risulta occupato, sposta ciò che lo occupa (esclusi muri)
};



typedef Room *pRoom;


#include "math.hpp"

#include "physical.hpp"
#include "character.hpp"

#include "enemies/enemies.hpp"
#include "items/artifacts.hpp"
#include "equipment/equipment.hpp"
#include "floor.hpp"
#include "wall.hpp"
#include "chest.hpp"


#endif