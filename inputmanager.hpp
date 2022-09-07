#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "timer.hpp"
#include <curses.h>

const int input_h=1;
const int input_l=2;

#define INPUT_TIMER_INDEX 0
#define INPUT_IMER_LIMIT (REFRESH_RATE)


class InputManager {
	private:
		int curr_input;
		WINDOW* input_window;
		Timer timer;
	public:
		InputManager(int x_win, int y_win);

		void calculate_input (); //calcola l'input

		int get_input();		//ritorna l'input corrente

};

typedef InputManager *pInputManager;



#endif