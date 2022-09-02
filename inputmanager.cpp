#include "inputmanager.hpp"


InputManager::InputManager(int x_win, int y_win) {
    input_window=newwin (y_win, x_win, input_h, input_l);
    keypad(input_window, true);
    nodelay(input_window, true);
    noecho();
    curs_set(0);		//cursore invisibile
	cbreak();			//Ctrl+C esce dal gioco
}

void InputManager::calculate_input(){
    curr_input=wgetch(input_window);
}

int InputManager::get_input(){
    calculate_input();
    return (curr_input);
}