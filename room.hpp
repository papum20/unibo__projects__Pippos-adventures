#ifndef ROOM_HPP
#define ROOM_HPP

#include "coordinate.hpp"


//direzioni (vettori unitari) (utili per la generazione di stanze e livelli)
#define DIR_SIZE 4
//define DIR_COORD 2
const Coordinate DIRECTIONS[DIR_SIZE] = {{0,-1},{1,0},{0,1},{-1,0}};
//per ogni indice i, DIR_CHANCES[i] è la probabilità di generare i percorsi a partire da un punto (nella generazione della stanza);
//la prima posizione indica la probabilità di generare in 0 nuove direzioni (cioè di fermarsi)
const int DIR_CHANCES[DIR_SIZE + 1] = {5, 20, 10, 3, 1};


#include "definitions.hpp"
#include "floor.hpp"
#include "maths.hpp"
#include "physical.hpp"
#include "union_find.hpp"
#include "wall.hpp"



class Room {
	private:
		int x, y;									//coordinate rispetto alla prima stanza del livello
		//istanze di muro e pavimento, riutilizzate sempre uguali
		pPhysical floorInstance;
		pPhysical wallInstance;

		// FUNZIONI
		// FUNZIONI AUSILIARIE SECONDARIE (USATE DALLE PRINCIPALI)
		void generatePath(Coordinate s, pUnionFind sets);		//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni, ne ritorna il numero
		// FUNZIONI AUSILIARIE GENERICHE (SEMPLICI E RICORRENTI)
		void swapPositions(Coordinate a, Coordinate b);

	protected:
		Coordinate size;	
		pPhysical grid[ROOM_HEIGHT][ROOM_WIDTH];	//array bidimensionale di oggetti fisici (presenti nelle loro posizioni)
		// FUNZIONI AUSILIARIE PRINCIPALI
		void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);						//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();										//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE

	public:
		Room(int x, int y);
		void recursiveDestroy();
		
		// GENERAZIONE
		void generate(); 										//genera uno schema randomico per i muri, inserendoli nell'array grid
//		void addNthDoor(int n);	//aggiunge una porta nell'n-esima posizione disponibile
		// DISEGNO
		void draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center);	//riempie l'array con le informazioni per stampare a schermo, con opportune modifiche di prospettiva e altro;
																									//inquadra solo un rettangolo con le dimensioni dei parametri intorno al giocatore
		// MOVIMENTO
		bool moveObject(Physical ob, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)

		// SET
		void makeConnection(Room *room, int dir);
		// GET
		int getX();
		int getY();
		Coordinate getSize();
		pPhysical checkPosition(Coordinate pos);		//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		Room *getConnectedRoom(Coordinate pos);			//ritorna il puntatore alla stanza collegata da una porta
};



typedef Room *pRoom;




#endif