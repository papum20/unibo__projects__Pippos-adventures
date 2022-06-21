#ifndef ROOM_HPP
#define ROOM_HPP

#include "level.hpp"

#include "union_find.hpp"

#include "physical.hpp"
#include "door.hpp"
#include "wall.hpp"
#include "floor.hpp"



#define X_SCALE 9							//coefficiente di "allargamento orizzontale" della stanza
#define ROOM_WIDTH (30 * X_SCALE)//320		//larghezza stanza
#define ROOM_HEIGHT 40//180					//altezza stanza

#define MAX_CONNECTED_R 5					//massimo numero di stanze collegate a ognuna
#define MAX_SIDES_R 4						//massimo numero di stanze (normali) collegate sui lati

//direzioni (vettori unitari) (utili per la generazione di stanze e livelli)
#define DIR_SIZE 4
#define DIR_COORD 2
const int DIRECTIONS[DIR_SIZE][DIR_COORD] = {{0,-1},{1,0},{0,1},{-1,0}};
//per ogni indice i, DIR_CHANCES[i] è la probabilità di generare i percorsi a partire da un punto (nella generazione della stanza);
//la prima posizione indica la probabilità di generare in 0 nuove direzioni (cioè di fermarsi)
const int DIR_CHANCES[DIR_SIZE + 1] = {5, 20, 10, 3, 1};




class Room {
	private:
		int x, y;									//coordinate rispetto alla prima stanza del livello

		int width;
		int height;	
		pPhysical grid[ROOM_HEIGHT][ROOM_WIDTH];	//array bidimensionale di oggetti fisici (presenti nelle loro posizioni)
	
		int n_doors_max;							//massimo numero porte (dimensione array)
		int n_doors_sides;							//numero di lati occupati da una porta (attualmente)
		pDoor doors[MAX_CONNECTED_R];				//array di puntatori a porte (che portano a stanze collegate);

		//istanze di muro e pavimento, riutilizzate sempre uguali
		pPhysical floorInstance;
		pPhysical wallInstance;

		// FUNZIONI
		void generate(); 										//genera uno schema randomico per i muri, inserendoli nell'array grid
		// FUNZIONI AUSILIARIE
		void generatePath(int x, int y, pUnionFind sets);		//genera un percorso casuale a partire da x,y

		int singleCoordinate(int x, int y);						//converte una coppia di coordinate x,y in una singola coordinata (sulle dimensioni width e height)
		void doubleCoordinate(int xy, int &x, int &y);			//converte una coordinata (sulle dimensioni width e height) in una coppia x,y
		bool validCoordinates(int x, int y, int xmin, int xmax, int ymin, int ymax);	//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		
	public:
		Room(int x, int y);
		// GENERAZIONE
//		void addNthDoor(int n);	//aggiunge una porta nell'n-esima posizione disponibile
		// CONTROLLO
		pPhysical checkPosition(int x, int y);	//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)

		// SET
		void makeConnection(Room *room, int dir);	//connects this room to "room" in direction dir (relative to this)
		// GET
		int getX();
		int getY();
		Room *getConnectedRoom(int dir);	//ritorna il puntatore alla stanza collegata in una data direzione dir
											//0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
//		int getSideDoors();				//ritorna il numero di lati occupati da una porta (attualmente)
};



typedef Room *pRoom;




#endif