#include "hud.hpp"


Hud::Hud(int x, int y, pPlayer p){
    max_health=p->maxHealth;
    max_stamina=p->maxStamina;
    player=p;
    start_x=x;
    start_y=y;
    hud_win= newwin (CAMERA_WIDTH, HUD_HEIGHT, y, x);
}

void Hud::drawHud (){
    int health_counter;             //serve a contare quanto della barra della vita colorare
    int stamina_counter;            //serve a contare quanto della barra della stamina colorare
    int y_cursor, x_cursor;         //indici che mi aiutano nel disegno
    int distance=30;                //distanza tra le icone dell'hud
    
    health_counter=(larghezza_blocchetto*n_blocchetti*(player->curHealth))/max_health;       //formula per calcolare quanta vita "percentuale" ha il personaggio
    stamina_counter=(larghezza_blocchetto*n_blocchetti*(player->curStamina))/max_stamina;

    init_pair (1, COLOR_BLACK, COLOR_RED);          //scritte nero sfondo rosso
    init_pair (2, COLOR_BLACK, COLOR_WHITE);        //scritte nero sfondo bianco
    init_pair (4, COLOR_RED, COLOR_BLACK);          //scritte rosse sfondo nero
    init_color(COLOR_GREEN, 625, 320, 175);        //marrone per lo zaino
    init_pair (5, COLOR_GREEN, COLOR_BLACK);        //scritte marroni sfondo nero
    
    //disegno la barra della vita
    y_cursor=1+start_y;
    x_cursor=6+start_x;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==2  && barra_vita[i][j]!='|' && health_counter>0){           //coloro di rosso se sono all'interno della barra (y_c), non sono alla fine 
                wattron(hud_win, COLOR_PAIR(1));                                  //di un segmento ('|') e ho ancora della vita da visualizzare (health_counter)
                mvwaddch(hud_win, y_cursor, x_cursor, barra_vita[i][j]);
                wattroff(hud_win, COLOR_PAIR(1));
                health_counter--;
            }
            else{
                mvwaddch(hud_win, y_cursor, x_cursor, barra_vita[i][j]);
            }
            x_cursor++;
        }
        y_cursor++;
        x_cursor=6+start_x;
    }
    wattron(hud_win, COLOR_PAIR(4));
    mvwprintw (hud_win, start_y+2, start_x+2, "HP");
    wattroff(hud_win, COLOR_PAIR(4));

    //disegno la barra della stamina
    y_cursor=3+start_y;
    x_cursor=6+start_x;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==4  && barra_stamina[i][j]!='/' && stamina_counter>0){            
                wattron(hud_win, COLOR_PAIR(2));                                  
                mvwaddch(hud_win, y_cursor, x_cursor, barra_stamina[i][j]);
                wattroff(hud_win, COLOR_PAIR(2));
                stamina_counter--;
            }
            else
                mvwaddch(hud_win, y_cursor, x_cursor, barra_stamina[i][j]);
            x_cursor++;
        }
        y_cursor++;
        x_cursor=6+start_x;
    }

    mvwprintw (hud_win, start_y+4, start_x+2, "ST");

    //le x di partenza da ora diventeranno variabili

    //disegno il numero di cuori
    x_cursor=x_cursor+barra_colonne+10;
    y_cursor=1+start_y;
    draw_number(x_cursor, y_cursor, player->n_hearts);

    //disegno il cuore
    x_cursor=x_cursor+number_columns+2;                                          //5 larghezza lettera                                               
    y_cursor=1+start_y;
    wattron(hud_win, COLOR_PAIR(4));                                //nota per me, scritte rosse sfondo nero
    for (int i=0; i<heart_rows; i++){
        for (int j=0; j<heart_columns; j++){
            mvwaddch(hud_win, y_cursor, x_cursor, cuore[i][j]);
            x_cursor++;
        }
        x_cursor=x_cursor-heart_columns;
        y_cursor++;
    }
    wattroff(hud_win, COLOR_PAIR(4));

    //disegno lettera per l'inventario
    wattron(hud_win, COLOR_PAIR(5));

    x_cursor=x_cursor+heart_columns+distance;
    y_cursor=2+start_y;
    draw_n(x_cursor, y_cursor);

    //disegno l'inventario
    x_cursor=x_cursor+n_columns+2;
    y_cursor=2+start_y;
    for (int i=0; i<inventary_rows; i++){
        for (int j=0; j<inventary_columns; j++){
           mvwaddch(hud_win, y_cursor, x_cursor, inventary[i][j]);
           x_cursor++; 
        }
        y_cursor++;
        x_cursor=x_cursor-inventary_columns;
    }

    wattroff(hud_win, COLOR_PAIR(5));

    //disegno i punti
    x_cursor=x_cursor+inventary_columns+distance;
    y_cursor=1+start_y;
    draw_p(x_cursor, y_cursor);

    //disegno i numeri
    x_cursor=x_cursor+p_columns+2;
    y_cursor=1+start_y;
    draw_points(x_cursor, y_cursor);

}

void Hud::draw_n(int x, int y){
    for (int i=0; i<n_rows; i++){
        for (int j=0; j<n_columns; j++){
            mvwaddch(hud_win, y, x, n[i][j]);
            x++;
        }
        y++;
        x=x-n_columns;
    }
}

void Hud::draw_p(int x, int y){
    for (int i=0; i<p_rows; i++){
        for (int j=0; j<p_columns; j++){
            mvwaddch(hud_win, y, x, p[i][j]);
            x++;
        }
        y++;
        x=x-p_columns;
    }
}

void Hud::draw_points(int x, int y){
    p_list head=NULL;
    int points;
    points=player->get_points();
    while (points!=0){
        head=head_insert(head, (points%10) );
        points=points/10;
    }
    while (head!=NULL){
        draw_number(x, y, head->val);
        head=head->next;
        x=x+number_columns+1;
    }
}

void Hud::draw_number(int x, int y, int number){
            switch (number){
                case 0:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, zero[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 1:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, one[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 2:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, two[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 3:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, three[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 4:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, four[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 5:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, five[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 6:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, six[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 7:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, seven[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 8:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, eight[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
                case 9:{
                    for (int i=0; i<number_rows; i++){
                        for (int j=0; j<number_columns; j++){
                            mvwaddch(hud_win, y, x, nine[i][j]);
                            x++;
                        }
                        y++;
                        x=x-number_columns;
                    }
                    break;
                }
            }
        }

p_list Hud::head_insert (p_list head, int x){
    if (head==NULL){
        head=new list;
        head->val=x;
        head->next=NULL;
        return head;
    }
    else{
        p_list tmp;
        tmp= new list;
        tmp->val=x;
        tmp->next=head;
        return tmp;
    }
}