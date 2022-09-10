#include "system_text.hpp"




System_text::System_text(int stdscr_x, int stdscr_y) {
text_x_pos = (stdscr_x - WINDOW_TEXT_WIDTH) / (2.2), text_y_pos = (stdscr_y - WINDOW_TEXT_HEIGHT) / (1.6);
this->text = newwin(WINDOW_TEXT_HEIGHT, WINDOW_TEXT_WIDTH, 10,10/*text_y_pos, text_x_pos*/);
is_open=false;
is_full=false;
space=1;
      
}


void System_text::destroy(){
    delwin(text);
}

bool System_text::is_active(){
    return(is_open);
}

void System_text::open(){
    is_open=true;
    box(text, 0, 0);
    mvwaddch(text, WINDOW_TEXT_HEIGHT - 3, 1, '_');
    for(int i=0; i<WINDOW_TEXT_WIDTH - 3; i++){
        waddch(text, '_');
    }
    
    /*mvwprintw(text, WINDOW_TEXT_HEIGHT - 2, 1, "HAI PERSO VITA");
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 4, 1, "HAI ATTACCATO MALE");
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 6, 1, "E' STREMANTE PROGRAMMARE");
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 8, 1, "HAI APERTO UNA CESTA");
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 10, 1, "HIA SUBITO DANNI");
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 12, 1, "BELLA");*/
    wrefresh(text);
}

void System_text::insert_string(const char string[]){
if(is_full){
    Pixel_art::clean_window(text, WINDOW_TEXT_HEIGHT - 2, WINDOW_TEXT_WIDTH - 1);
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 2, 1,string);
}
else{
    mvwprintw(text, WINDOW_TEXT_HEIGHT - (space*2), 1,string);
    space++;
    if(space>=5)
        is_full=true;
}    
}

void System_text::insert_number(int danno){
if(is_full){
    //Pixel_art::clean_window(text, WINDOW_TEXT_HEIGHT - 2, WINDOW_TEXT_WIDTH - 1);
    mvwprintw(text, WINDOW_TEXT_HEIGHT - 2, 1,string);
}
else{
    mvwprintw(text, WINDOW_TEXT_HEIGHT - (space*2), 1,string);
    space++;
    if(space>=5)
        is_full=true;
}    
}

void System_text::close(){
    is_open=false;
    werase(text);
    wrefresh(text);
}
