#include "inputmanager.hpp"


InputManager::InputManager(WINDOW* win) {
    input_window=win;
}

InputManager::calculate_input(){
    curr_input=wgetch(input_window);
}

InputManager::get_input(){
    InputManager::calculate_input();
    return (curr_input);
}