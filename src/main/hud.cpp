#include "main/hud.hpp"


Hud::Hud(int x, int y, pPlayer p):Overlay(){
    max_health=p->maxHealth;
    max_stamina=p->maxStamina;
    player=p;
    start_x=x;
    start_y=y;
    hud_win= newwin (HUD_HEIGHT, HUD_WIDTH, y, x);
    box(hud_win,0,0);
    wrefresh(hud_win);
}

void Hud::destroy() {
    Overlay::destroy();
}

void Hud::drawHud (){

    box(hud_win, 0, 0);
    
    int health_counter;             //serve a contare quanto della barra della vita colorare
    int stamina_counter;            //serve a contare quanto della barra della stamina colorare
    int y_cursor, x_cursor;         //indici che mi aiutano nel disegno
    int distance=15;                //distanza tra le icone dell'hud
    
    health_counter=(larghezza_blocchetto*n_blocchetti*(player->curHealth))/max_health;       //formula per calcolare quanta vita "percentuale" ha il personaggio
    stamina_counter=(larghezza_blocchetto*n_blocchetti*(player->curStamina))/max_stamina;
    
    //disegno la barra della vita
    y_cursor=1;
    x_cursor=6;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==2  && barra_vita[i][j]!='|' && health_counter>0){           //coloro di rosso se sono all'interno della barra (y_c), non sono alla fine 
                wattron(hud_win, COLORE_VITA);                                  //di un segmento ('|') e ho ancora della vita da visualizzare (health_counter)
                mvwaddch(hud_win, y_cursor, x_cursor, barra_vita[i][j]);
                wattroff(hud_win, COLORE_VITA);
                health_counter--;
            }
            else{
                mvwaddch(hud_win, y_cursor, x_cursor, barra_vita[i][j]);
            }
            x_cursor++;
        }
        y_cursor++;
        x_cursor=6;
    }
    wattron(hud_win, COLORE_CUORE);
    mvwprintw (hud_win, 2, 2, "HP");
    wattroff(hud_win, COLORE_CUORE);

    //disegno la barra della stamina
    y_cursor=3;
    x_cursor=6;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==4  && barra_stamina[i][j]!='/' && stamina_counter>0){            
                wattron(hud_win, COLORE_STAMINA);                                  
                mvwaddch(hud_win, y_cursor, x_cursor, barra_stamina[i][j]);
                wattroff(hud_win, COLORE_STAMINA);
                stamina_counter--;
            }
            else{
                mvwaddch(hud_win, y_cursor, x_cursor, barra_stamina[i][j]);
            }
            x_cursor++;
        }
        y_cursor++;
        x_cursor=6;
    }

    mvwprintw (hud_win, 4, 2, "ST");

    //le x di partenza da ora diventeranno variabili

    //disegno il numero di cuori
    x_cursor=x_cursor+barra_colonne+10;
    y_cursor=1;
    draw_number(x_cursor, y_cursor, player->n_hearts);

    //disegno il cuore
    x_cursor=x_cursor+number_columns+2;                                          //5 larghezza lettera                                               
    y_cursor=1;
    wattron(hud_win, COLORE_CUORE);                                //nota per me, scritte rosse sfondo nero
    for (int i=0; i<heart_rows; i++){
        for (int j=0; j<heart_columns; j++){
            mvwaddch(hud_win, y_cursor, x_cursor, cuore[i][j]);
            x_cursor++;
        }
        x_cursor=x_cursor-heart_columns;
        y_cursor++;
    }
    wattroff(hud_win, COLORE_CUORE);

    //disegno le chiavi

    x_cursor=x_cursor+heart_columns+distance;
    y_cursor=1;
    draw_number(x_cursor, y_cursor, player->n_keys);
    
    wattron(hud_win, COLORE_INVENTARIO);
    x_cursor=x_cursor+n_columns+2;
    y_cursor=2;
    for (int i=0; i<key_rows; i++){
        for (int j=0; j<key_columns; j++){
           mvwaddch(hud_win, y_cursor, x_cursor, key[i][j]);
           x_cursor++; 
        }
        y_cursor++;
        x_cursor=x_cursor-key_columns;
    }
    wattroff(hud_win, COLORE_INVENTARIO);
    
    //disegno lettera per l'inventario
    wattron(hud_win, COLORE_INVENTARIO);

    x_cursor=x_cursor+key_columns+distance;
    y_cursor=2;
    draw_n(x_cursor, y_cursor);

    //disegno l'inventario
    x_cursor=x_cursor+n_columns+2;
    y_cursor=2;
    for (int i=0; i<inventary_rows; i++){
        for (int j=0; j<inventary_columns; j++){
           mvwaddch(hud_win, y_cursor, x_cursor, inventary[i][j]);
           x_cursor++; 
        }
        y_cursor++;
        x_cursor=x_cursor-inventary_columns;
    }

    wattroff(hud_win, COLORE_INVENTARIO);

    //disegno i punti
    x_cursor=x_cursor+inventary_columns+distance;
    y_cursor=1;
    draw_p(x_cursor, y_cursor);

    //disegno i numeri
    x_cursor=x_cursor+p_columns+2;
    y_cursor=1;
    draw_points(x_cursor, y_cursor);

    wrefresh(hud_win);
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
    points=player->getPoints();
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

void Hud::setPlayer(pPlayer player) {
    this->player = player;
}