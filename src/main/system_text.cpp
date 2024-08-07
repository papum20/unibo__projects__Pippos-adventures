#include "main/system_text.hpp"


char window_write[messages_saved][max_words];


System_text::System_text(int stdscr_x, int stdscr_y):Overlay(),Pixel_art() {
    this->text = newwin(WINDOW_TEXT_HEIGHT, WINDOW_TEXT_WIDTH,stdscr_y, stdscr_x);
    is_open=false;
    space=0; 
}


void System_text::destroy(){
    delwin(text);
    Overlay::destroy();
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
    wrefresh(text);
}

void System_text::insert_string(const char string[]){
    space++;
    if(space>messages_saved)
        space=messages_saved;
        for(int i=space-1; i>0;i--){
            char tmp[max_words];
            strcpy(tmp, window_write[i]);
            strcpy(window_write[i], window_write[i-1]);
            strcpy(window_write[i-1], tmp);
        }
        strcpy (window_write[0], string);
    clean_window(text, WINDOW_TEXT_HEIGHT - 2, WINDOW_TEXT_WIDTH - 1);
    open();
    int j=1;
    for(int i=0; i<space; i++){       
        int k=0;
        while(window_write[i][k]!='\0'){
                mvwaddch(text, WINDOW_TEXT_HEIGHT - (j*2), k+1, window_write[i][k]);
            k++;
        }
        while(k<WINDOW_TEXT_WIDTH-4) {
            mvwaddch(text,  WINDOW_TEXT_HEIGHT - (j*2), k+1, ' ');
            k++;
        }
        j++;
    }   
    wrefresh(text);
}

void System_text::close(){
    is_open=false;
    werase(text);
    wrefresh(text);
}
