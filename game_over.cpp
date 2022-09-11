#include "game_over.hpp"




Game_over::Game_over(int stdscr_x, int stdscr_y):Overlay(),Pixel_art() {
w_x_pos = (stdscr_x - WINDOW_G_O_WIDTH) / 2, w_y_pos = (stdscr_y - WINDOW_G_O_HEIGHT) / 2;
this->window = newwin(WINDOW_G_O_HEIGHT, WINDOW_G_O_WIDTH,w_y_pos, w_x_pos);
}


bool Game_over::isGameOver(){
    return(is_open);
}

void Game_over::open(){
    is_open=true;
    box(window, 1, 0);
    pixel_phrase(window, 1, 1, "GAME OVER", true);
    wrefresh(window);
}

