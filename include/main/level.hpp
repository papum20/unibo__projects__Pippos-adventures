//// GESTISCE TUTTO CIÒ CHE RIGUARDA LO SCHERMO IN GIOCO : CONTIENE UN PUNTATORE ALLA STANZA CORRENTE, LA QUALE MEMORIZZA TUTTE LE ENTITÀ PRESENTI IN ESSA,
//// E SI OCCUPA DI DISEGNARLA A SCHERMO, GESTENDO ANCHE UNA TELECAMERA CHE NE INQUADRA ADEGUATAMENTE UNA PORZIONE



#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdlib>
#include <curses.h>
#include "main/coordinate.hpp"
#include "main/math.hpp"
#include "main/overlay.hpp"


//// COSTANTI DI INIZIALIZZAZIONE ATTRIBUTI DI LEVEL
#define LR_BORDER 1
#define TB_BORDER 1
const Coordinate LEVEL_SIZE = Coordinate(N_ROOMS, N_ROOMS);
const Coordinate LEVEL_CENTER = LEVEL_SIZE.times(.5, .5).integer();		//dove viene spawnata la prima stanza


#include "main/cell.hpp"
#include "main/boss_room.hpp"
#include "main/definitions.hpp"
#include "enemies/enemies.hpp"
#include "equipment/equipment.hpp"
#include "main/player.hpp"
#include "structures/priority_queue_room.hpp"
#include "main/system_text.hpp"
#include "main/timer.hpp"








class Level : public Overlay {
	private:
		//spessore bordi laterali (lr) e sopra e sotto (tb)
		int lr_border;
		int tb_border;
		//stanze nel livello
		pRoom map[LEVEL_AREA];
		Coordinate map_size;

		int level;					//livello corrente

		//schermo:
		chtype screen[CAMERA_HEIGHT][CAMERA_WIDTH];	//array bidimensionale contenente le informazioni delle celle dello schermo (ciò che viene stampato)
		//oggetti:
		pRoom curRoom;				//stanza attuale, inquadrata e in cui si trova il giocatore
		pPlayer player;
		Timer timer;
		System_text *log;
		
		// FUNZIONI
		void generateMap();						//genera lo schema della disposizione delle stanze del livello
		void changeRoom();						//controlla se si deve cambiare stanza, ed eventualmente la cambia
		void nextLevel();						//passa al livello successivo
		
		// FUNZIONI AUSILIARIE
		void setUp(int win_x, int win_y, int win_w, int win_h, pPlayer player, System_text *log = NULL);	//setup per costruttore
		void destroyRooms();
		lock_type randLockedDoor(Room A, Room B);														//(per generate) ritorna casualmente se la/le porta/e tra la stanza da generare e room devono essere bloccate
		pConnectedRoom findRoomAtCoordinates(pConnectedRoom rooms[], int len, Coordinate c);			//ritorna la stanza dell'array con tali coordinate (NULL se non presente)


	public:
		Level(int win_x, int win_y, pPlayer player, System_text *log);
		Level(int win_x, int win_y, int win_w, int win_h, pPlayer player);
		void destroy();		
		void open();								//disegna tutto da capo

		void update(int input);						//da richiamare a ogni frame
		void display();								//stampa la parte di stanza inquadrata nello schermo (chiamato a ogni frame, se non in pausa), con camera che segue il personaggio
		void displayAtPosition(Coordinate center);

		// GET
		void getLevelMap(pRoom map[LEVEL_AREA]);
		int getLevel();
		Coordinate getSize();
		pRoom getCurrentRoom();

		// SET
		void setPivot(pPhysical pivot);											//imposta l'oggetto che la telecamera seguirà
		void setDefaultCameraSpecs();											//reimposta le caratteristiche di default della camera
};

typedef Level *pLevel;


#endif

