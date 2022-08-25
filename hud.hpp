#ifndef HUD_HPP
#define HUD_HPP

#include <ncurses.h>
#include "main.hpp"
#include "pixel_art.hpp"

using namespace std;

const int barra_righe=2;
const int barra_colonne=46;
const int larghezza_blocchetto=8;
const int n_blocchetti=5;

const int heart_rows=5;
const int heart_columns=6;

const int inventary_rows=4;
const int inventary_columns=8;

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


class Hud {
	private:
		WINDOW* hud_win;
		int x_win;
		int y_win;
		int max_health;
		int max_stamina;
		Pixel_art pix;

		int points;
	public:
		Hud(WINDOW* win, int max_h, int max_s, int p);
		//costruttore
		void drawHud(int curr_health, int curr_st, int hearts);		//disegna hud (in gioco)
		//void startMenu();	//inizializza il menu (quando si preme il tasto pausa)
		//void updateMenu();	//disegna menu (solo se in pausa)
		void change_points(int delta);
};





#endif