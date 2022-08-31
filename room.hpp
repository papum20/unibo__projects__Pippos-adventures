#ifndef ROOM_HPP
#define ROOM_HPP


#include "coordinate.hpp"
#include "definitions.hpp"


//direzioni (vettori unitari) (utili per la generazione di stanze e livelli)
#define DIRECTIONS_N 4
//define DIR_COORD 2
#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
const Coordinate DIRECTIONS[DIRECTIONS_N] = {{0,-1},{1,0},{0,1},{-1,0}};
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


#include "enemies/enemies.hpp"
#include "items/items.hpp"
#include "equipment/equipment.hpp"
#include "floor.hpp"
#include "wall.hpp"

#include "enemy.hpp"
#include "map.hpp"
#include "math.hpp"
#include "physical.hpp"
#include "map.hpp"
#include "union_find.hpp"



class Room {
	private:
		Coordinate pos;											//coordinate rispetto alla prima stanza del livello
		//istanze di muro e pavimento, riutilizzate sempre uguali
		pInanimate floorInstance;
		pInanimate wallInstance;

		// FUNZIONI
		// FUNZIONI AUSILIARIE SECONDARIE (USATE DALLE PRINCIPALI)
/*		void generatePath(Coordinate s, pUnionFind sets);			//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
*/					//e directions con le rispettive direzioni, ne ritorna il numero
		//bool isSpawnAllowed(s_coord pos, Coordinate size);			//bool se può essere generato qualcosa di dimensioni size in posizione pos, cioè se non c'è altro nel mezzo
		int getFreeCells(s_coord available[], Coordinate size);		//modifica l'array con le celle disponibili per lo spawn di qualcosa di dimensione size e ne ritorna il numero
		// FUNZIONI AUSILIARIE GENERICHE (SEMPLICI E RICORRENTI)

	protected:
		int scale_x;
		pMap map;

		// FUNZIONI AUSILIARIE PRINCIPALI
		/*void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);						//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();										//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE
*/
	public:
		Room(Coordinate pos);
		void recursiveDestroy();								//elimina tutti i puntatori contenuti nella stanza, agendo poi ricorsivamente sulle stanze collegate
		void update(char input);								//da richiamare a ogni frame; chiama l'update di ogni elemento nella stanza
		
		// GENERAZIONE
		void generate(); 										//genera uno schema randomico per i muri, inserendoli nell'array map
//		void addNthDoor(int n);	//aggiunge una porta nell'n-esima posizione disponibile
		void spawnEnemy(pEnemy enemy);							//spawna un nemico
		void spawnChest(pChest chest);							//spawna una chest
		// DISEGNO
		void draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center);	//riempie l'array con le informazioni per stampare a schermo, con opportune modifiche di prospettiva e altro;
																									//inquadra solo un rettangolo con le dimensioni dei parametri intorno al giocatore

		// GET
		Coordinate getPos();
		Coordinate getSize();
		void getMap(pPhysical map[], Coordinate &size);			//modifica mappa, ritorna dimensioni
		virtual pRoom getRoomInPosition(Coordinate pos);		//ritorna il puntatore alla stanza collegata da una porta in posizione pos

		// SET
		virtual void makeConnection(Room *room, int dir, lock_type lt, bool first = true);	//collega l'altra stanza a questa (se è connectedRoom), con stato bloccato lt; first inizializzato da solo
		bool setPosition_strong(pPhysical obj, Coordinate pos);								//posiziona obj in pos e, se lo spazio risulta occupato, sposta ciò che lo occupa (esclusi muri)
};



typedef Room *pRoom;




#endif