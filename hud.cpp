#include "hud.hpp"


Hud::Hud(WINDOW* win, int max_h, int max_s){
    hud_win=win;
    getmaxyx(hud_win, y_win, x_win);
    max_health=max_h;
    max_stamina=max_s;	
}

Hud::drawHud (int curr_health, int curr_st, int hearts){
    int health_counter;             //serve a contare quanto della barra della vita colorare
    int stamina_counter;            //serve a contare quanto della barra della stamina colorare
    health_counter=(larghezza_blocchetto*n_blocchetti*curr_health)/max_health;       //formula per calcolare quanta vita "percentuale" ha il personaggio
    stamina_counter=(larghezza_blocchetto*n_blocchetti*curr_st)/max_stamina;

    int y_cursor, x_cursor;         //indici che mi aiutano nel disegno

    int distance=30;                //distanza tra le icone dell'hud

    //disegno la barra della vita
    y_cursor=2;
    x_cursor=6;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==3  && barra_vita[i][j]!='|' && health_counter>0){           //coloro di rosso se sono all'interno della barra (y_c), non sono alla fine 
                wattron(game_window, COLOR_PAIR(1));                                  //di un segmento ('|') e ho ancora della vita da visualizzare (health_counter)
                mvwaddch(game_window, y_cursor, x_cursor, barra_vita[i][j]);
                wattroff(game_window, COLOR_PAIR(1));
                health_counter--;
            }
            else
                mvwaddch(game_window, y_cursor, x_cursor, barra_vita[i][j]);
            x_cursor++;
        }
        y_cursor++;
        x_cursor=6;
    }

    //disegno la barra della stamina
    y_cursor=5;
    x_cursor=6;
    for (int i=0; i<barra_righe; i++){
        for (int j=0; j<barra_colonne; j++){
            if (y_cursor==6  && barra_stamina[i][j]!='/' && stamina_counter>0){            
                wattron(game_window, COLOR_PAIR(2));                                  
                mvwaddch(game_window, y_cursor, x_cursor, barra_stamina[i][j]);
                wattroff(game_window, COLOR_PAIR(2));
                stamina_counter--;
            }
            else
                mvwaddch(game_window, y_cursor, x_cursor, barra_stamina[i][j]);
            x_cursor++;
        }
        y_cursor;
        x_cursor=6;
    }

    //le x di partenza da ora diventeranno variabili

    //disegno il numero di cuori
    x_cursor=x_cursor+barra_colonne+10;
    y_cursor=2;


    //disegno il cuore
    x_cursor=x_cursor+2;                                                //nota per me, +larghezza pausa
    y_cursor=2;
    wattron(game_window, COLOR_PAIR(4));                                //nota per me, scritte rosse sfondo nero
    for (int i=0; i<heart_rows; i++){
        for (int j=0; j<heart_columns; j++){
            mvwaddch(game_window, y_cursor, x_cursor, cuore[i][j]);
            x_cursor++;
        }
        x_cursor=x_cursor-heart_columns;
        y_cursor++;
    }
    wattroff(game_window, COLOR_PAIR(4));


    //disegno l'inventario
    x_cursor=x_cursor+heart_columns+distance;
    y_cursor=3;
    for (int i=0; i<inventary_rows; i++){
        for (int j=0; j<inventary_columns; j++){
           mvwaddch(game_window, y_cursor, x_cursor, inventary[i][j]);
           x_cursor++; 
        }
        y_cursor++;
        x_cursor=x_cursor-inventary_columns;
    }

}