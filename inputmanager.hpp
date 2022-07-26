#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "timer.hpp"
#include <ncurses.h>

const int input_h=1;
const int input_l=2;

class InputManager {
	private:
		Timer timer;
		int curr_input;
		WINDOW* input_window;
	public:
		InputManager(int x_win, int y_win);

		void calculate_input (); //calcola l'input

		char get_input();		//ritorna un puntatore all'input corrente

};




#endif