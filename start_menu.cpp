#include "start_menu.hpp"


Start_menu::Start_menu(int stdscr_x, int stdscr_y):Pixel_art(),Overlay() {
options_x_pos = (stdscr_x - MENU_OPTIONS_WIDTH) / (2.3), options_y_pos = (stdscr_y - MENU_OPTIONS_HEIGHT) / (1.7);
face_x_pos = (stdscr_x - FACE_WIDTH) / (5.6), face_y_pos = (stdscr_y - FACE_HEIGHT) / (1.65);
menu_x_pos = (stdscr_x - MENU_WIDTH) / (2.2), menu_y_pos = (stdscr_y - MENU_HEIGHT) / (1.6);


this->menu_is_active=false;

this->menu = newwin(MENU_HEIGHT, MENU_WIDTH, menu_y_pos, menu_x_pos);
this->wface = newwin(FACE_HEIGHT, FACE_WIDTH, face_y_pos, face_x_pos);
this->caverna = newwin(stdscr_y, stdscr_x, 0, 0);
this->w_options = newwin(MENU_OPTIONS_HEIGHT, MENU_OPTIONS_WIDTH, options_y_pos, options_x_pos);
highlight=0;
options_is_active=false;
}

void Start_menu::destroy(){
    delwin(menu);
    delwin(wface);
    delwin(caverna);
    delwin(w_options);
}

void Start_menu::open_options(){
    options_is_active=true;
    keypad(menu,false);
    werase(wface);
    werase(menu);
    wrefresh(wface);
    wrefresh(menu);
    print_cave();
    box(w_options, 0, 0);
    mvwaddch(w_options, 2, 2, KEY_PAUSE);
    wprintw(w_options, " = apri e chiudi menu di pausa");
    mvwaddch(w_options, 4, 2, KEY_ESC);
    wprintw(w_options, " = torni indietro nei menu");
    mvwprintw(w_options, 6, 2, "barra spaziatrice = tasto per interagire");
    mvwaddch(w_options, 8, 2, KEY_MAP);
    wprintw(w_options, " = apri la minimappa");
    mvwprintw(w_options, 10, 2, "invio = tasto di selezione nei menu");
    mvwprintw(w_options, 12, 2, "i tasti freccia servono a muoversi nelle 4 direzioni");
    mvwprintw(w_options, 14, 2, "i tasti w a s d servono ad attaccare nelle 4 direzioni");
    mvwprintw(w_options, 16, 2, "si può attaccare pure con ctrl + frecce direzionali");
    wrefresh(w_options);
}

void Start_menu::update_options(){
        if(input==KEY_ESC){
            keypad(menu,true);
            werase(w_options);
            wrefresh(w_options);
            options_is_active=false;
        }
}

bool Start_menu::is_active(){
    return(menu_is_active);
}

void Start_menu::close(){
    default_color();
    menu_is_active=false;
    werase(wface);
    werase(menu);
    werase(caverna);
    wrefresh(wface);
    wrefresh(menu);
    wrefresh(caverna);
}

void Start_menu::update(bool &isRunning, int input){
    this->input=input;
        if(options_is_active==true){
            update_options();
            
            if(options_is_active==false){
            open();
            }
        return;   
       }
       
       if(input==scroll_up){
        highlight--;
        if(highlight==-1)
            highlight=0;
       }
       if(input==scroll_down){
        highlight++;
        if(highlight==3)
            highlight=2;
       }
      
       if((highlight==1) &&(input==KEY_SELECT_MENU)){
        open_options();
       }
       else if(((highlight==0) || (highlight==2)) &&(input==KEY_SELECT_MENU)){
        close();
        if(highlight == 2) isRunning = false;
       } else {
            int high_letter=3;
            for(int i=0; i<3; i++){
                if(i==highlight){
                        pixel_phrase(menu, 10, high_letter, choices[i], true);
                        high_letter=high_letter+6;
                }
                    else{
                        pixel_phrase(menu, 10, high_letter, choices[i], false);
                        high_letter=high_letter+6;
                    }
            }
            wrefresh (menu);
       }
   
   }


void Start_menu::set_menu_color(){
        init_color(COLOR_CYAN, 239, 86, 0); // crea il marrone scuro
        init_color(COLOR_MAGENTA, 474, 321, 192); // crea il marrone chiaro
        init_color(COLOR_BLUE, 90, 454, 47);//VERDE SCURO
        
}

void Start_menu::print_cave(){

set_menu_color();
for(int i = 0; i < c_hight; i++){
    for(int j = 0; j <c_lenght; j++){
        if(cave[i][j]==0){
            wattron(caverna, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_CYAN)));
            mvwaddch(caverna, i*3, j*3, ' ');
            mvwaddch(caverna, i*3 + 1, j*3, ' ');
            mvwaddch(caverna, i*3 + 2, j*3, ' ');
            mvwaddch(caverna, i*3, j*3 + 1, ' ');
            mvwaddch(caverna, i*3, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 1, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 1, ' ');
            }
        if(cave[i][j]==1){
            wattron(caverna, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_MAGENTA)));
            mvwaddch(caverna, i*3, j*3, ' ');
            mvwaddch(caverna, i*3 + 1, j*3, ' ');
            mvwaddch(caverna, i*3 + 2, j*3, ' ');
            mvwaddch(caverna, i*3, j*3 + 1, ' ');
            mvwaddch(caverna, i*3, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 1, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 1, ' ');}
        if(cave[i][j]==2){
            wattron(caverna, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_GREEN)));
            mvwaddch(caverna, i*3, j*3, ' ');
            mvwaddch(caverna, i*3 + 1, j*3, ' ');
            mvwaddch(caverna, i*3 + 2, j*3, ' ');
            mvwaddch(caverna, i*3, j*3 + 1, ' ');
            mvwaddch(caverna, i*3, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 1, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 1, ' ');}
        if(cave[i][j]==3){
            wattron(caverna, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK)));
            mvwaddch(caverna, i*3, j*3, ' ');
            mvwaddch(caverna, i*3 + 1, j*3, ' ');
            mvwaddch(caverna, i*3 + 2, j*3, ' ');
            mvwaddch(caverna, i*3, j*3 + 1, ' ');
            mvwaddch(caverna, i*3, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 1, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 1, ' ');}
        if(cave[i][j]==4){
            wattron(caverna, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLUE)));
            mvwaddch(caverna, i*3, j*3, ' ');
            mvwaddch(caverna, i*3 + 1, j*3, ' ');
            mvwaddch(caverna, i*3 + 2, j*3, ' ');
            mvwaddch(caverna, i*3, j*3 + 1, ' ');
            mvwaddch(caverna, i*3, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 1, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 1, j*3 + 2, ' ');
            mvwaddch(caverna, i*3 + 2, j*3 + 1, ' ');}
    }
}
wrefresh(caverna);

}



void Start_menu::open(){
menu_is_active=true;
print_cave();
print_face(wface, face, 65, 32);
box(menu, 0, 0);
keypad(menu, true);   

int high_letter=3;
       for(int i=0; i<3; i++){
           if(i==highlight){
                pixel_phrase(menu, 10, high_letter, choices[i], true);
                high_letter=high_letter+6;
           }
            else{
                pixel_phrase(menu, 10, high_letter, choices[i], false);
                high_letter=high_letter+6;
            }
       }
}


