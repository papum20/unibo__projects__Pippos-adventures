#include "menu.hpp"


Menu::Menu(int menu_y_pos, int menu_x_pos, int options_x_pos, int options_y_pos, int face_y_pos, int face_x_pos):Pixel_art() {
this->menu_y_pos=menu_y_pos;
this->menu_x_pos=menu_x_pos;
this->options_y_pos=options_y_pos;
this->options_x_pos=options_x_pos;
this->face_y_pos=face_y_pos;
this->face_x_pos=face_x_pos;
this->menu_is_active=false;

this->menu = newwin(25, 60, menu_y_pos, menu_x_pos);
this->wface = newwin(33, 66, face_y_pos, face_x_pos);
this->caverna = newwin(110, 350, 0, 0);
this->w_options = newwin(30, 75, options_y_pos, options_x_pos);
highlight=0;
options_is_active=false;
}


void Menu::open_options(){
    clean_window(menu, menu_y_pos, menu_x_pos);
    options_is_active=true;
    keypad(menu,false);
    werase(wface);
    werase(menu);
    wrefresh(wface);
    wrefresh(menu);
    print_cave();
    box(w_options, 0, 0);
    mvwprintw(w_options, 2, 2, "m = apri menu");
    mvwprintw(w_options, 4, 2, "n = apri inventario");
    mvwprintw(w_options, 6, 2, "i tasti w a s d servono a muoversi nelle 4 direzioni");
    wrefresh(w_options);
}

void Menu::update_options(){
        if(input==KEY_ESC){
            keypad(menu,true);
            werase(w_options);
            wrefresh(w_options);
            options_is_active=false;
        }
}

bool Menu::is_active(){
    return(menu_is_active);
}

void Menu::close_menu(){
    default_color();
    menu_is_active=false;
    werase(wface);
    werase(menu);
    werase(caverna);
    wrefresh(wface);
    wrefresh(menu);
    wrefresh(caverna);
}

void Menu::update(bool &isRunning, int input){
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
       if(((highlight==0) || (highlight==2)) &&(input==KEY_SELECT_MENU)){
        close_menu();
        if(highlight == 2) isRunning = false;
       }
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
   
   wrefresh(menu);
   }


void Menu::set_menu_color(){
        init_color(COLOR_CYAN, 239, 86, 0); // crea il marrone scuro
        init_color(COLOR_MAGENTA, 474, 321, 192); // crea il marrone chiaro
        init_color(COLOR_BLUE, 90, 454, 47);//VERDE SCURO
        
}

void Menu::print_cave(){

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



void Menu::open(){
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


