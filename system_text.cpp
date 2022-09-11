#include "system_text.hpp"


char window_write[6][max_words];

System_text::System_text(int stdscr_x, int stdscr_y):Overlay() {
text_x_pos = (stdscr_x - WINDOW_TEXT_WIDTH) / (2.2), text_y_pos = (stdscr_y - WINDOW_TEXT_HEIGHT) / (1.6);
this->text = newwin(WINDOW_TEXT_HEIGHT, WINDOW_TEXT_WIDTH,text_y_pos, text_x_pos);
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
if(space>6){
space=6;
   for(int i=space-1; i>0;i--){
        char tmp[max_words];
        strcpy(tmp, window_write[i]);
        strcpy(window_write[i], window_write[i-1]);
            strcpy(window_write[i-1], tmp);
    }
strcpy (window_write[0], string);

}
else{
    strcpy (window_write[space-1], string);
}
clean_window(text, WINDOW_TEXT_HEIGHT - 2, WINDOW_TEXT_WIDTH - 1);
open();
int j=1;
    for(int i=0; i<space; i++){
        
        int k=0;
        while(window_write[i][k]!='\0'){
            mvwaddch(text, WINDOW_TEXT_HEIGHT - (j*2), k+1, window_write[i][k]);
            k++;
        }
        j++;
    }   

wrefresh(text);
}

void System_text::clean_window(WINDOW* window, int w_hight, int w_lenght){
wattron(window, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK))); 
for(int i=1; i<w_hight; i++){
    for(int j=1; j<w_lenght; j++){
        mvwaddch(window, i, j, ' ');
    }
}
wattroff(window, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK)));   
}

void System_text::close(){
    is_open=false;
    werase(text);
    wrefresh(text);
}
