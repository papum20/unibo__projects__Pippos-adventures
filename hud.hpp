#ifndef HUD_HPP
#define HUD_HPP

#include <curses.h>
#include "player.hpp"
#include "cell.hpp"

const int COLORE_VITA = Cell (0, COLOR_BLACK, COLOR_RED, 0).colorPair();
const int COLORE_STAMINA = Cell (0, COLOR_BLACK, COLOR_WHITE, 0).colorPair();
const int COLORE_INVENTARIO = Cell (0, COLOR_BROWN, COLOR_BLACK, 0).colorPair();
const int COLORE_CUORE = Cell (0, COLOR_RED, COLOR_BLACK, 0).colorPair();

using namespace std;

struct list{
    int val;
    list* next;
};

typedef list* p_list;

#define HUD_WIDTH 200
#define HUD_HEIGHT 15

const int n_rows=4;
const int n_columns=6;

const int p_rows=5;
const int p_columns=6;

const int barra_righe=2;
const int barra_colonne=46;
const int larghezza_blocchetto=8;
const int n_blocchetti=5;

const int heart_rows=5;
const int heart_columns=6;

const int inventary_rows=4;
const int inventary_columns=8;

const int number_rows=5;
const int number_columns=5;

const char barra_vita[barra_righe][barra_colonne]= 
{ {' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' '}, 
  {'|', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|'} 
};
const char barra_stamina[barra_righe][barra_colonne]= 
{ {' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' '}, 
  {'/', '_', '_', '_', '_', '_', '_', '_', '_', '/', '_', '_', '_', '_', '_', '_', '_', '_', '/', '_', '_', '_', '_', '_', '_', '_', '_', '/', '_', '_', '_', '_', '_', '_', '_', '_', '/', '_', '_', '_', '_', '_', '_', '_', '_', '/'} 
};

const char cuore[heart_rows][heart_columns]=
{ {' ', '_', ' ', ' ', '_', ' '}, 
  {'/', '*', '\\', '/', '*', '\\'},
  {'\\', '*', '*', '*', '*', '/'},
  {' ', '\\', '*', '*', '/', ' '},
  {' ', ' ', '\\', '/', ' ', ' '}
};

const char inventary[inventary_rows][inventary_columns]=
{ {' ', '_', '_', '(', ')', '_', '_', ' '},
  {'|', '_', '_', ' ', ' ', '_', '_', '|'},
  {'|', ' ', ' ', 'O', 'O', ' ', ' ', '|'},
  {'|', '_', '_', '_', '_', '_', '_', '|'}
};

const char n[n_rows][n_columns]=
{ {'|', '\\', ' ', ' ', ' ', '|'},
  {'|', ' ', '\\', ' ', ' ', '|'},
  {'|', ' ', ' ', '\\', ' ', '|'},
  {'|', ' ', ' ', ' ', '\\', '|'},
};

const char p[p_rows][p_columns]=
{ {' ', '_', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '_', '|'},
  {'|', ' ', ' ', ' ', ' ', ' '},
  {'|', ' ', ' ', ' ', ' ', ' '}
};

const char zero[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', '|'},
  {'|', ' ', ' ', ' ', '|'},
  {'|', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '|'}	
};

const char one[number_rows][number_columns]=
{ {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', '/', '|', ' '},
  {' ', '/', ' ', '|', ' '},
  {' ', ' ', ' ', '|', ' '},
  {' ', ' ', ' ', '|', ' '}	
};

const char two[number_rows][number_columns]=
{ {'_', '_', '_', '_', ' '},
  {' ', ' ', ' ', ' ', '|'},
  {' ', '_', '_', '_', '|'},
  {'|', ' ', ' ', ' ', ' '},
  {'|', '_', '_', '_', '_'}	
};

const char three[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {' ', ' ', ' ', ' ', '|'},
  {' ', '_', '_', '_', '|'},
  {' ', ' ', ' ', ' ', '|'},
  {' ', '_', '_', '_', '|'}	
};

const char four[number_rows][number_columns]=
{ {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', '/', ' ', ' '},
  {' ', '/', ' ', ' ', ' '},
  {'/', '_', '_', '_', '|'},
  {' ', ' ', ' ', ' ', '|'}	
};

const char five[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', ' '},
  {'|', '_', '_', '_', ' '},
  {' ', ' ', ' ', ' ', '|'},
  {' ', '_', '_', '_', '|'}	
};

const char six[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', ' '},
  {'|', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '|'}	
};

const char seven[number_rows][number_columns]=
{ {'_', '_', '_', '_', '_'},
  {' ', ' ', ' ', ' ', '/'},
  {' ', ' ', ' ', '/', ' '},
  {' ', ' ', '/', ' ', ' '},
  {' ', '/', ' ', ' ', ' '}	
};

const char eight[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '|'},
  {'|', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '|'}	
};

const char nine[number_rows][number_columns]=
{ {' ', '_', '_', '_', ' '},
  {'|', ' ', ' ', ' ', '|'},
  {'|', '_', '_', '_', '|'},
  {' ', ' ', ' ', ' ', '|'},
  {' ', '_', '_', '_', '|'}	
};


class Hud {
	private:
		int x_win;
		int y_win;
		int max_health;
		int max_stamina;
    pPlayer player;
    int start_x;
    int start_y;
	public:
    WINDOW* hud_win;
    Hud(int x, int y, pPlayer p);

		void drawHud();		//disegna hud (in gioco)
    void draw_number(int x, int y, int number);
    void draw_points(int x, int y);
    void draw_n(int x, int y);
    void draw_p(int x, int y);
		//void drawHud(int curr_health, int curr_st, int hearts);		//disegna hud (in gioco)
		//void startMenu();	//inizializza il menu (quando si preme il tasto pausa)
		//void updateMenu();	//disegna menu (solo se in pausa)

    p_list head_insert (p_list head, int x);
};



#endif