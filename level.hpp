//// GESTISCE TUTTO CIÒ CHE RIGUARDA LO SCHERMO IN GIOCO : CONTIENE UN PUNTATORE ALLA STANZA CORRENTE, LA QUALE MEMORIZZA TUTTE LE ENTITÀ PRESENTI IN ESSA,
//// E SI OCCUPA DI DISEGNARLA A SCHERMO, GESTENDO ANCHE UNA TELECAMERA CHE NE INQUADRA ADEGUATAMENTE UNA PORZIONE



#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdlib>
#include <curses.h>
#include "coordinate.hpp"
#include "math.hpp"


//// COSTANTI DI INIZIALIZZAZIONE ATTRIBUTI DI LEVEL
#define LR_BORDER 1
#define TB_BORDER 1
#define N_ROOMS 10						//numero di stanze (normali) generate per livello
#define LEVEL_AREA (N_ROOMS * N_ROOMS)	//dimensioni matrice livello
#define LEVELS_N 5

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

//SPAWN
const int ENEMIES_N[LEVELS_N] {10};
#define ENEMIES_N_MAX 10
const Enemy ENEMIES_INSTANCES[LEVELS_N][ENEMIES_N_MAX] = 	{
															{}
															};
const int ENEMIES_CHANCHES[LEVELS_N][ENEMIES_N_MAX]		= 	{
															{1}
															};
const int ENEMIES_CHANCE_TOT[LEVELS_N] = {1};


#include "cell.hpp"
#include "connected_room.hpp"
#include "definitions.hpp"
#include "enemies/enemies.hpp"
#include "player.hpp"
#include "priority_queue_room.hpp"
#include "timer.hpp"



class Level {
	private:
		//dimensioni dello schermo disponibile, ovvero della parte di stanza disegnata a schermo
		int width;
		int height;
		//spessore bordi laterali (lr) e sopra e sotto (tb)
		int lr_border;
		int tb_border;
		//stanze nel livello
		pRoom map[LEVEL_AREA];

		int level;					//livello corrente

		//camera: caratteristiche
		Coordinate offset_max;		//massimo spostamento della camera
		float speed;				//tempo (secondi) per raggiungere il massimo spostamento
		float damping_speed;		//tempo (secondi) per tornare da massimo spostamento a posizione di riposo
		float damping_timeout;		//tempo di attesa prima di tornare alla posizione di riposo
		float opposite_speed;		//tempo per tornare da massimo spostamento a posizione di riposo quando ci si inizia a muovere nella posizione opposta
		float change_pivot_speed;	//tempo per spostarsi su un nuovo pivot
		Coordinate position;
		Coordinate lastMovement;
		pPhysical pivot;			//la camera segue un oggetto physical
		bool pivotChanged;			//se è cambiato il pivot
		Coordinate pivotDistance;	//(se è cambiato il pivot) distanza dal vecchio pivot

		//schermo:
		WINDOW *levelWindow;
		chtype screen[CAMERA_HEIGHT][CAMERA_WIDTH];	//array bidimensionale contenente le informazioni delle celle dello schermo (ciò che viene stampato)
		//oggetti:
		//int n_rooms;				//numero di stanze (normali) generate per livello
		pRoom curRoom;		//stanza attuale, inquadrata e in cui si trova il giocatore
		pPlayer player;
		Timer timer;
		
		// FUNZIONI
		void generateMap();						//genera lo schema della disposizione delle stanze del livello
		void spawnInRoom(pConnectedRoom room);	//spawn iniziale di nemici
		void changeRoom();						//controlla se si deve cambiare stanza, ed eventualmente la cambia
		void nextLevel();						//passa al livello successivo
		
		// FUNZIONI AUSILIARIE
		lock_type randLockedDoor(Room A, Room B);												//(per generate) ritorna casualmente se la/le porta/e tra la stanza da generare e room devono essere bloccate
		pConnectedRoom findRoomAtCoordinates(pConnectedRoom rooms[], int len, Coordinate c);	//ritorna la stanza dell'array con tali coordinate (NULL se non presente)
		void cameraUpdate();																	//calcola il centro della camera
		Coordinate cameraStart();																//prima casella inquadrata
		Coordinate cameraEnd();																	//ultima casella inquadrata
		pEnemy randEnemy();																		//ritorna un nemico casuale

	public:
		Level(int win_y, int win_x, pPlayer player);
		Level(int win_y, int win_x, int win_h, int win_w, pPlayer player);

		void display();								//stampa la parte di stanza inquadrata nello schermo (chiamato a ogni frame, se non in pausa), con camera che segue il personaggio
		void displayAtPosition(Coordinate center);

		void update(char input);					//da richiamare a ogni frame

		// GET
		void getLevelMap(pRoom map[]);
		void getRoomMap(pPhysical map[], Coordinate &size, pPlayer &player);	//ritorna (modifica) mappa (disposizione stanze), dimensioni (della matrice del livello), playerr

		// SET
		void setPivot(pPhysical pivot);											//imposta l'oggetto che la telecamera seguirà
		void setDefaultCameraSpecs();											//reimposta le caratteristiche di default della camera

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