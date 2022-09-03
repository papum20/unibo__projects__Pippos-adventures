#ifndef MAIN_HPP
#define MAIN_HPP


//#include <cstdlib>
#include <curses.h>
#include <ctime>
#include "level.hpp"
#include "hud.hpp"
#include "inputmanager.hpp"
#include "menu.hpp"
#include "player.hpp"


//// INIT
	void cursesInit();	//inizializza funzioni di ncurses
	void gameInit();	//inizializzazioni di gioco
	void colorsInit();	//inizializza/modifica i colori

//// END
	void cursesEnd();
	void gameEnd();


#endif