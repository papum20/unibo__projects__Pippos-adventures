#include "inputmanager.hpp"


InputManager::InputManager(int x_win, int y_win) {
    input_window=newwin (input_h+2, input_l+2, y_win, x_win);
    keypad(input_window, true);
    nodelay(input_window, true);
    noecho();
    curs_set(0);		//cursore invisibile
	cbreak();			//Ctrl+C esce dal gioco
}

void InputManager::calculate_input(){
    curr_input=mvwgetch(input_window, 0, 0);
}

int InputManager::get_input(){
    return (curr_input);
}