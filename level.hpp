#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdlib>
#include <curses.h>
#include "coordinate.hpp"


//// COSTANTI DI INIZIALIZZAZIONE ATTRIBUTI DI LEVEL
#define LR_BORDER 1
#define TB_BORDER 1
#define N_ROOMS 10			//numero di stanze (normali) generate per livello

// COSTANTI PER L'IMPLEMENTAZIONE DELLA GENERAZIONE
//dimensioni della matrice available (per generateMap)
#define MAX_AVAILABLE (N_ROOMS * 2 + 2)
#define DIM_AVAILABLE 3
//indice di x,y,n nella matrice
#define AV_X 0
#define AV_Y 1
#define AV_N 2
#define MAX_RAND_EXEC 3		//massimo numero di esecuzione di cicli che terminano solo in base a un numero random
#define GENERATION_CHANCE 2	//usato come probabilità in generateMap()

// COSTANTI PER IL MOVIMENTO DELLA CAMERA
const Coordinate CAMERA_OFFSET_MAX(15, 8);	//massimo spostamento della camera
#define CAMERA_SPEED 2.						//tempo (secondi) per raggiungere il massimo spostamento
#define CAMERA_DAMPING_SPEED 1.				//tempo (secondi) per tornare da massimo spostamento a posizione di riposo
#define CAMERA_DAMPING_TIMEOUT 1.2			//tempo di attesa prima di tornare alla posizione di riposo
#define CAMERA_OPPOSITE_SPEED .6			//tempo per tornare da massimo spostamento a posizione di riposo quando ci si inizia a muovere nella posizione opposta
#define CAMERA_CHANGE_PIVOT_SPEED 2.		//tempo per spostarsi su un nuovo pivot

/*#define CAMERA_OFFSET_MAX_X 15			//massimo spostamento della camera
#define CAMERA_OFFSET_MAX_Y 8
#define CAMERA_SPEED_X 2.				//tempo (secondi) per raggiungere il massimo spostamento
#define CAMERA_SPEED_Y 2.
#define CAMERA_DAMPING_SPEED_X 1.		//tempo (secondi) per tornare da massimo spostamento a posizione di riposo
#define CAMERA_DAMPING_SPEED_Y 1.
#define CAMERA_DAMPING_TIME_X 1.2		//tempo di attesa prima di tornare alla posizione di riposo
#define CAMERA_DAMPING_TIME_Y 1.2
#define CAMERA_OPPOSITE_SPEED_X .6		//tempo per tornare da massimo spostamento a posizione di riposo quando ci si inizia a muovere nella posizione opposta
#define CAMERA_OPPOSITE_SPEED_Y .6
#define CAMERA_CHANGE_PIVOT_SPEED_X 2.	//tempo per spostarsi su un nuovo pivot
#define CAMERA_CHANGE_PIVOT_SPEED_Y 2.*/

//TIMER
#define CAMERA_DAMPING_TIMER 0


#include "cell.hpp"
#include "connected_room.hpp"
#include "definitions.hpp"
#include "player.hpp"
#include "timer.hpp"



class Level {
	private:
		//dimensioni dello schermo disponibile, ovvero della parte di stanza disegnata a schermo
		int width;
		int height;
		//spessore bordi laterali (lr) e sopra e sotto (tb)
		int lr_border;
		int tb_border;
		//camera
		Coordinate offset_max;		//massimo spostamento della camera
		float speed;				//tempo (secondi) per raggiungere il massimo spostamento
		float damping_speed;		//tempo (secondi) per tornare da massimo spostamento a posizione di riposo
		float damping_timeout;		//tempo di attesa prima di tornare alla posizione di riposo
		float opposite_speed;		//tempo per tornare da massimo spostamento a posizione di riposo quando ci si inizia a muovere nella posizione opposta
		float change_pivot_speed;	//tempo per spostarsi su un nuovo pivot
		/*float camera_offset_max_x;			//massimo spostamento della camera
		float camera_offset_max_y;
		float camera_speed_x;				//tempo (secondi) per raggiungere il massimo spostamento
		float camera_speed_y;
		float camera_damping_speed_x;		//tempo (secondi) per tornare da massimo spostamento a posizione di riposo
		float camera_damping_speed_y;
		float camera_damping_time_x;		//tempo di attesa prima di tornare alla posizione di riposo
		float camera_damping_time_y;
		float camera_opposite_speed_x;		//tempo per tornare da massimo spostamento a posizione di riposo quando ci si inizia a muovere nella posizione opposta
		float camera_opposite_speed_y;
		float camera_change_pivot_speed_x;	//tempo per spostarsi su un nuovo pivot
		float camera_change_pivot_speed_y;*/

		Coordinate position;
		Coordinate lastMovement;
		pPhysical pivot;			//la camera segue un oggetto physical
		bool pivotChanged;		//se è cambiato il pivot
		Coordinate pivotDistance;	//(se è cambiato il pivot) distanza dal vecchio pivot
		//schermo
		WINDOW *levelWindow;
		chtype screen[CAMERA_HEIGHT][CAMERA_WIDTH];	//array bidimensionale contenente le informazioni delle celle dello schermo (ciò che viene stampato)
		//oggetti
		//int n_rooms;			//numero di stanze (normali) generate per livello
		pRoom curRoom;			//stanza attuale, inquadrata e in cui si trova il giocatore
		pPlayer player;
		Timer timer;
		
		// FUNZIONI
		void generateMap();		//genera lo schema della disposizione delle stanze del livello

		void changeRoom();
		void nextLevel();	
		
		pCRoom findRoomAtCoordinates(pCRoom rooms[], int len, int x, int y);			//ritorna la stanza dell'array con tali coordinate (NULL se non presente)
		// FUNZIONI AUSILIARIE
		int findCellAtCoordinates(int A[MAX_AVAILABLE][DIM_AVAILABLE], int x, int y);	//ritorna l'indice della posizione dell'array con tali coordinate (-1 se non presenteS)
		void switchQueue(int A[MAX_AVAILABLE][DIM_AVAILABLE], int a, int b);			//scambia due elementi di A
		void checkMinHeap(int H[MAX_AVAILABLE][DIM_AVAILABLE], int len, int i);			//aggiusta una posizione del min-heap (mantenendone le proprietà)
		void cameraUpdate();															//calcola il centro della camera

		Coordinate cameraStart();														//prima casella inquadrata
		Coordinate cameraEnd();															//ultima inquadrata

	public:
		Level(int win_y, int win_x, pPlayer player);
		Level(int win_y, int win_x, int win_h, int win_w, pPlayer player);

		void display();								//stampa la parte di stanza inquadrata nello schermo (chiamato a ogni frame, se non in pausa), con camera che segue il personaggio
		void displayAtPosition(Coordinate center);

		void update();								//da richiamare a ogni frame

		// SET
		void setPivot(pPhysical pivot);
		void setDefaultCameraSpecs();				//reimposta le caratteristiche di default della camera

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