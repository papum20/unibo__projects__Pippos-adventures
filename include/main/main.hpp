#ifndef MAIN_HPP
#define MAIN_HPP


//#include <cstdlib>
#include <curses.h>
#include <ctime>
#include "main/definitions.hpp"

#include "main/game_over.hpp"
#include "main/hud.hpp"
#include "main/inputmanager.hpp"
#include "main/minimap.hpp"
#include "main/pause_menu.hpp"
#include "main/start_menu.hpp"
#include "main/system_text.hpp"

#include "main/level.hpp"
#include "main/player.hpp"


//// INIT
	void cursesInit();	//inizializza funzioni di ncurses
	void gameInit();	//inizializzazioni di gioco
	void colorsInit();	//inizializza/modifica i colori

//// END
	void cursesEnd();
	void gameEnd();

//// FUNCTIONS
	void initDebug(WINDOW *win);
	void printDebug(WINDOW *win, int level, int seconds, int fps);
	int int_to_string(int n, char out[]);		//per n >= 0, altrimenti ritorna -1



#endif