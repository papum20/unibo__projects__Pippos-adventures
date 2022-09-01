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


//// REFRESH RATE : durata di un frame
#define FRAMES_PER_SECOND 30					//aggiornamenti in un secondo
#define REFRESH_RATE (1. / FRAMES_PER_SECOND)	//durata di un aggiornamento
#define REFRESH_TIMER_INDEX 0					//indice del timer (implementazione)


//// INIT
	void cursesInit();
	void gameInit();

//// END
	void cursesEnd();


#endif