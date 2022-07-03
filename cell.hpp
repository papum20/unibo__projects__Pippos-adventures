//// RAPPRESENTA UNA CELLA DA STAMPARE

#ifndef CELL_HPP
#define CELL_HPP

#include <curses.h>


#define COLORS_TOT 8

// ATTRIBUTI DI DEFAULT
#define CELL_DFLT_CHAR ' '
#define CELL_DFLT_FG COLOR_WHITE
#define CELL_DFLT_BG COLOR_BLACK
#define CELL_DFLT_ATTR A_NORMAL	//nessun attributo


class Cell {
	private:
		char ch;	//char
		int fg, bg;	//colore testo / sfondo
		attr_t att;	//attributi

	public:
		Cell();
		Cell(char ch, int fg, int bg, attr_t att);		//valori minori di 0 inizializzano di default

		void edit(char ch, int fg, int bg, attr_t att);	//valori minori di 0 non modificano
		// GET
		char getCh();
		chtype toChtype();								//converte in unico valore chtype
		int colorPairNumber();
		int colorPair();
};



#endif