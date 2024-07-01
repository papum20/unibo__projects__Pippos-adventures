#include "main/inputmanager.hpp"


InputManager::InputManager(int x_win, int y_win):Overlay() {
    input_window=newwin (input_h+2, input_l+2, y_win, x_win);
    keypad(input_window, true);
    nodelay(input_window, true);
    noecho();
    curs_set(0);		//cursore invisibile
	cbreak();			//Ctrl+C esce dal gioco

    timer.set_max(INPUT_TIMER_INDEX, INPUT_IMER_LIMIT);
    timer.start(INPUT_TIMER_INDEX);
}
void InputManager::destroy() {
    Overlay::destroy();
}

void InputManager::calculate_input(){
    //se non riceve input può comunque restituire l'ultimo preso, se non è sato preso troppo tempo fa
    //infatti il terminale non è molto preciso a prendere l'input e spesso potrebbe non prenderlo per un singolo frame
    //(motivo per cui si rende necessaria tale implementazione)
    int input=mvwgetch(input_window, 0, 0);
    if(input != ERR) {
        curr_input = input;
        timer.start(INPUT_TIMER_INDEX);
    }
    else if(timer.check(INPUT_TIMER_INDEX)) {
        curr_input = ERR;
    }
}

int InputManager::get_input(){
    return (curr_input);
}