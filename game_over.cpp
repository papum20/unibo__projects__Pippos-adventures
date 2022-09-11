#include "game_over.hpp"




Game_over::Game_over(int stdscr_x, int stdscr_y, pPlayer player):Overlay(),Pixel_art() {
    w_x_pos = (stdscr_x - WINDOW_G_O_WIDTH) / 2, w_y_pos = (stdscr_y - WINDOW_G_O_HEIGHT) / 2;
    this->window = newwin(WINDOW_G_O_HEIGHT, WINDOW_G_O_WIDTH,w_y_pos, w_x_pos);
    is_game_over = false;
    this->player =player;
}


bool Game_over::isGameOver(){
    return is_game_over;
}
void Game_over::update() {
    if(player->getHealth() <= 0) is_game_over = true;
}

void Game_over::open(){
    is_open=true;
    box(window, 1, 0);
    pixel_phrase(window, 1, 1, "GAME OVER", true);
    wrefresh(window);
}




void Game_over::setPlayer(pPlayer player) {
    this->player = player;
}