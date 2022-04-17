#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <curses.h>
#include "room.hpp"


#define CAMERA_WIDTH 135
#define CAMERA_HEIGHT 35
#define N_ROOMS 10

//const short wallColors[5] = {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA};
//const short floorColors[5] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};



class Level {
	private:
		//dimensioni dello schermo disponibile, ovvero della parte di stanza disegnata a schermo
		int width;
		int height;
		//short wallColor;
		//short floorColor;

		pRoom curRoom;			//stanza attuale, inquadrata e in cui si trova il giocatore
		
		// FUNZIONI
		void generateMap();		//genera lo schema della disposizione delle stanze del livello
		
	public:
		Level();

		void draw();			//disegna la parte di stanza inquadrata nello schermo (chiamato a ogni frame, se non in pausa)
		

		//genera una stanza (come array bidimensionale)
		//generateAll();
		//genera tutte le stanze
};



#endif


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