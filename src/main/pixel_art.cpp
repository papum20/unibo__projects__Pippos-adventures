#include "main/pixel_art.hpp"



Pixel_art::Pixel_art() {
    color_content(COLOR_CYAN, &d_r_cyan, &d_g_cyan, &d_b_cyan);
    color_content(COLOR_MAGENTA, &d_r_magenta, &d_g_magenta, &d_b_magenta);
    color_content(COLOR_BLUE, &d_r_blue, &d_g_blue, &d_b_blue);
    color_content(COLOR_GREEN, &d_r_green, &d_g_green, &d_b_green);
    color_content(COLOR_BROWN, &d_r_brown, &d_g_brown, &d_b_brown);
	
      
}

void Pixel_art::default_color(){
init_color(COLOR_CYAN, d_r_cyan, d_g_cyan, d_b_cyan);
init_color(COLOR_MAGENTA, d_r_magenta, d_g_magenta, d_b_magenta); 
init_color(COLOR_BLUE, d_r_blue, d_g_blue, d_b_blue); 
init_color(COLOR_GREEN, d_r_green, d_g_green, d_b_green); 
init_color(COLOR_BROWN, d_r_brown, d_g_brown, d_b_brown); 
}

void Pixel_art::convert_char_to_pixel(WINDOW* menu, int start_x, int start_y, char c, bool highlight){
    for(int i=0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(highlight==false){
                wattron(menu, COLOR_PAIR(Cell::pairNumber(COLOR_GREEN, COLOR_WHITE)));
            }
            else{
                wattron(menu, COLOR_PAIR(Cell::pairNumber(COLOR_GREEN, COLOR_YELLOW))); 
            }
        if(c=='A' || c== 'a'){
            if(ALPHABET[0][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='B' || c== 'b'){
            if(ALPHABET[1][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }else if(c=='C' || c== 'c'){
            if(ALPHABET[2][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='D' || c== 'd'){
            if(ALPHABET[3][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='E' || c== 'e'){
            if(ALPHABET[4][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='F' || c== 'f'){
            if(ALPHABET[5][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='G' || c== 'g'){
            if(ALPHABET[6][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='H' || c== 'h'){
            if(ALPHABET[7][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='I' || c== 'i'){
            if(ALPHABET[8][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='L' || c== 'l'){
            if(ALPHABET[9][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='M' || c== 'm'){
            if(ALPHABET[10][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='N' || c== 'n'){
            if(ALPHABET[11][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='O' || c== 'o'){
            if(ALPHABET[12][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='P' || c== 'p'){
            if(ALPHABET[13][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='Q' || c== 'q'){
            if(ALPHABET[14][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='R' || c== 'r'){
            if(ALPHABET[15][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='S' || c== 's'){
            if(ALPHABET[16][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='T' || c== 't'){
            if(ALPHABET[17][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='U' || c== 'u'){
            if(ALPHABET[18][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='V' || c== 'v'){
            if(ALPHABET[19][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='Z' || c== 'z'){
            if(ALPHABET[20][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==39){
            if(ALPHABET[21][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='J' || c== 'j'){
            if(ALPHABET[22][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='K' || c== 'k'){
            if(ALPHABET[23][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='X' || c== 'x'){
            if(ALPHABET[24][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if(c=='Y' || c== 'y'){
            if(ALPHABET[25][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==63){
            if(ALPHABET[26][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==33){
            if(ALPHABET[27][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==49){
            if(ALPHABET[28][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==50){
            if(ALPHABET[29][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==51){
            if(ALPHABET[30][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==52){
            if(ALPHABET[31][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
        else if((int)c==53){
            if(ALPHABET[32][i][j]==1)
                mvwprintw(menu, i + start_y, j + start_x, " ");
        }
    }
    }
    wattroff(menu, COLOR_PAIR(Cell::pairNumber(COLOR_GREEN, COLOR_WHITE)));
    wattroff(menu, COLOR_PAIR(Cell::pairNumber(COLOR_GREEN, COLOR_YELLOW)));
    wrefresh(menu);
}


void Pixel_art::pixel_phrase(WINDOW* menu, int start_x, int start_y, const char string[], bool highlight){
int i=0;
int j=0;
if(highlight==true){
while(string[i] != '\0'){
convert_char_to_pixel(menu, start_x + j, start_y, string[i], true);    
i++;
j=j+6;
}
}
else{
while(string[i] != '\0'){
convert_char_to_pixel(menu, start_x + j, start_y, string[i], false); 
i++;
j=j+6;
}
}
}


void Pixel_art::clean_window(WINDOW* window, int w_hight, int w_lenght){
wattron(window, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK))); 
for(int i=1; i<w_hight; i++){
    for(int j=1; j<w_lenght; j++){
        mvwaddch(window, i, j, ' ');
    }
}
wattroff(window, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK)));   
}

void Pixel_art::print_face(WINDOW* facewin, const bool face[][face_lenght], int face_lenght, int face_hight){ 
int r;
box(facewin, 0, 0);    
 for(int i=1; i<face_hight; i++){
        for(int j=1; j<face_lenght; j++){
            if(face[i][j]==0){
                wattron(facewin, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
            }
            else if(face[i][j]==1){
                wattron(facewin, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK)));
            } 
            r=rand()%(2);  
            if(r==0) 
                mvwaddch(facewin, i, j, (char)(48));
            else 
                mvwaddch(facewin, i, j, (char)(49));
        }
    }
wattroff(facewin, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
wattroff(facewin, COLOR_PAIR(Cell::pairNumber(COLOR_BLACK, COLOR_BLACK)));
wrefresh(facewin);
}
