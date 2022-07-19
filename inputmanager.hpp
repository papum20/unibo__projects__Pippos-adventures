#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "timer.hpp"
#include <ncurses.h>

const double refresh_rate=

class InputManager {
	private:
		Timer timer;
		char* curr_input;
		WINDOW* input_window;
	public:
		InputManager(WINDOW* win);

		void calculate_input (); //calcola l'input

		char* get_input();		//ritorna un puntatore all'input corrente

};




#endif