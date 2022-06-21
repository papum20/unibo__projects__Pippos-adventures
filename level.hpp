#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdlib>
#include <curses.h>
#include "room.hpp"


#define CAMERA_WIDTH 135	//larghezza (massima) inquadratura livello
#define CAMERA_HEIGHT 35	//altezza (massima) inquadratura livello
#define N_ROOMS 10			//numero di stanze (normali) generate per livello

//dimensioni della matrice available (per generateMap)
#define MAX_AVAILABLE (N_ROOMS * 2 + 2)
#define DIM_AVAILABLE 3
//indice di x,y,n nella matrice
#define AV_X 0
#define AV_Y 1
#define AV_N 2

#define MAX_RAND_EXEC 3		//massimo numero di esecuzione di cicli che terminano solo in base a un numero random
#define GENERATION_CHANCE 2	//usato come probabilità in generateMap()

//const int wallColors[5] = {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA};
//const int floorColors[5] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};



class Level {
	private:
		//dimensioni dello schermo disponibile, ovvero della parte di stanza disegnata a schermo
		int width;
		int height;
		//int wallColor;
		//int floorColor;

		//int n_rooms;			//numero di stanze (normali) generate per livello
		pRoom curRoom;			//stanza attuale, inquadrata e in cui si trova il giocatore
		
		// FUNZIONI
		void generateMap();		//genera lo schema della disposizione delle stanze del livello

		// FUNZIONI AUSILIARIE
		pRoom findRoomAtCoordinates(pRoom rooms[], int len, int x, int y);				//ritorna la stanza dell'array con tali coordinate (NULL se non presente)
		int findCellAtCoordinates(int A[MAX_AVAILABLE][DIM_AVAILABLE], int x, int y);	//ritorna l'indice della posizione dell'array con tali coordinate (-1 se non presenteS)
		void switchQueue(int A[MAX_AVAILABLE][DIM_AVAILABLE], int a, int b);				//scambia due elementi di A
		void checkMinHeap(int H[MAX_AVAILABLE][DIM_AVAILABLE], int len, int i);				//aggiusta una posizione del min-heap (mantenendone le proprietà)

	public:
		Level();

		void draw();			//disegna la parte di stanza inquadrata nello schermo (chiamato a ogni frame, se non in pausa)
		

		//genera una stanza (come array bidimensionale)
		//generateAll();
		//genera tutte le stanze
};



#endif


////APPUNTI:

//generateMap():
/*IMPLEMENTAZIONE:
int r = rand() % DIR_SIZE: serve a randomizzare la direzione da cui iniziare a controllare le celle
adiacenti, altrimenti nel min-heap si avrebbe in testa sempre la stessa direzione, per esempio l'indice
0 sarebbe la direzione in alto, e quindi si avrebbero mappe tendenzialmente allungate, nel caso dell'esempio
mappe verticali, perché la testa del min-heap ha maggiore probabilità di uscire, e una volta uscita nella
maggior parte dei casi la nuova cella disponibile (che si va a mettere nella stessa posizione, nell'array, della
cella appena usata) si trova sulla stessa direzione - da cui le mappe dritte (verticali)
*/
/*COSTO: tempo=O(n**2), memoria=O(n+(2n+2))=O(n); con n=N_ROOMS
APPUNTO1: con rooms e avail implementati con AVL (forse) si avrebbe un costo logartmico
	per ricerca, inserimento... e quindi costo totale (n log n), con n=N_ROOMS
APPUNTO2: si possono togliere gli attributi x,y della classe e calcolarli ogni volta
	(presumibilmente senza variazione di costo in tempo)
*/


/*
[mxR=numero tot stanze; cuR=numero attuale stanze create]
GENERARE TUTTO INSIEME:
1)con array mxR x mxR + array mxR:
	-creo e genero una stanza (e inserisco in vettore) (O(1))
	-ogni volta scelgo una stanza dal vettore (O(mxR)), scelgo una direzione disponibile casuale (O(4)), ci creo una stanza, la aggiungo al vettore (e alla matrice)
	-se una stanza ne ha 4 collegate, la tolgo dal vettore
	-per ogni stanza creata, la genero con collegate quelle collegate nella matrice (O(mxR+4))
	tempo=O(mxR), memoria=O(mxR**2+mxR)=O(mxR**2)
2) senza matrici:
	-come per una stanza alla volta
GENEREARE UNA STANZA ALLA VOLTA:
-creo un puntatore a una stanza e la genero, con un numero di porte tra min(1,mxR-cuR) e min(4,mxR-cuR), con puntatore a stanze create ma non generate (O(1))
-ogni volta (O(mxR)) che il giocatore attraversa una porta: se non è stata generata:
	-cerco ogni stanza per vedere se è collegata a questa e ottengo un numero M (>=1 per la prima stanza a cui è collegata) (O(mxR),con strutture (O(log mxR)))
	-la genero con un numero di porte tra M e min(4,mxR-cuR)
	tempo=mxR * secondo step=O(mxR**2), con strutture O(mxR log mxR), memoria=O(1), con strutture O(mxR)
*/