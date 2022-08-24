#ifndef ROOM_HPP
#define ROOM_HPP


#include "coordinate.hpp"
#include "definitions.hpp"


//direzioni (vettori unitari) (utili per la generazione di stanze e livelli)
#define DIR_TOT 4
//define DIR_COORD 2
const Coordinate DIRECTIONS[DIR_TOT] = {{0,-1},{1,0},{0,1},{-1,0}};
//per ogni indice i, DIR_CHANCES[i] è la probabilità di generare i percorsi a partire da un punto (nella generazione della stanza);
//la prima posizione indica la probabilità di generare in 0 nuove direzioni (cioè di fermarsi)
const int DIR_CHANCES[DIR_TOT + 1] = {5, 20, 10, 3, 1};


#include "character.hpp"
#include "enemy.hpp"
#include "floor.hpp"
#include "maths.hpp"
#include "physical.hpp"
#include "projectile.hpp"
#include "union_find.hpp"
#include "wall.hpp"




class Room {
	private:
		Coordinate pos;											//coordinate rispetto alla prima stanza del livello
		//istanze di muro e pavimento, riutilizzate sempre uguali
		pInanimate floorInstance;
		pInanimate wallInstance;

		// FUNZIONI
		// FUNZIONI AUSILIARIE SECONDARIE (USATE DALLE PRINCIPALI)
		void generatePath(Coordinate s, pUnionFind sets);			//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], s_coord currentSet);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero
		int getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie border con i muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni, ne ritorna il numero
		bool isSpawnAllowed(s_coord pos, Coordinate size);			//bool se può essere generato qualcosa di dimensioni size in posizione pos, cioè se non c'è altro nel mezzo
		int getFreeCells(s_coord available[], Coordinate size);		//modifica l'array con le celle disponibili per lo spawn di qualcosa di dimensione size e ne ritorna il numero
		// FUNZIONI AUSILIARIE GENERICHE (SEMPLICI E RICORRENTI)

	protected:
		Coordinate size;
		int scale_x;
		pInanimate map[ROOM_AREA];
		pCharacter characters[ROOM_AREA];
		pProjectile projectiles[ROOM_AREA];

		// FUNZIONI AUSILIARIE PRINCIPALI
		void generateSidesWalls();
		void generateInnerRoom();
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);						//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();										//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE

	public:
		Room(Coordinate pos);
		void recursiveDestroy();								//elimina tutti i puntatori contenuti nella stanza, agendo poi ricorsivamente sulle stanze collegate
		void update(char input);								//da richiamare a ogni frame; chiama l'update di ogni elemento nella stanza
		
		// GENERAZIONE
		void generate(); 										//genera uno schema randomico per i muri, inserendoli nell'array map
//		void addNthDoor(int n);	//aggiunge una porta nell'n-esima posizione disponibile
		void spawnEnemy(pEnemy enemy);							//spawna un nemico
		// DISEGNO
		void draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center);	//riempie l'array con le informazioni per stampare a schermo, con opportune modifiche di prospettiva e altro;
																									//inquadra solo un rettangolo con le dimensioni dei parametri intorno al giocatore

		// GET
		Coordinate getPos();
		Coordinate getSize();
		void getMap(pInanimate map[], Coordinate &size);		//modifica mappa, ritorna dimensioni
		pPhysical checkPosition(Coordinate pos);				//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		pCharacter checkLine(Coordinate start, Coordinate end);	//checkPosition per una linea da start a end
};



typedef Room *pRoom;




#endif