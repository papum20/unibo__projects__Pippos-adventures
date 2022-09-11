#ifndef MAIN_HPP
#define MAIN_HPP


//#include <cstdlib>
#include <curses.h>
#include <ctime>
#include "definitions.hpp"

#include "game_over.hpp"
#include "hud.hpp"
#include "inputmanager.hpp"
#include "minimap.hpp"
#include "pause_menu.hpp"
#include "start_menu.hpp"
#include "system_text.hpp"

#include "level.hpp"
#include "player.hpp"


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