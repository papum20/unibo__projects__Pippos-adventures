#ifndef MAIN_HPP
#define MAIN_HPP


#include <iostream>
#include <curses.h>
#include <ctime>
#include "level.hpp"
#include "inputmanager.hpp"
#include "player.hpp"


//// INIT

void cursesInit();

void gameInit();


//// END


void cursesEnd();



#endif