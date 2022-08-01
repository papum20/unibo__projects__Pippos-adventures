#include "inputmanager.hpp"


InputManager::InputManager(int x_win, int y_win) {
    input_window=newwin (y_win, x_win, input_h, input_l);
}

void InputManager::calculate_input(){
    curr_input=wgetch(input_window);
}

char InputManager::get_input(){
    calculate_input();
    return (curr_input);
}