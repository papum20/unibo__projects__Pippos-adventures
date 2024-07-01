//// RAPPRESENTA UNA CELLA DA STAMPARE
// contiene le informazioni di carattere, colori testo/sfondo e attributi, e permette di ottenere il relativo chtype, stampabile con ncurses, con la funzione toChtype()

#ifndef CELL_HPP
#define CELL_HPP

#include <curses.h>
#include "main/definitions.hpp"


// ATTRIBUTI DI DEFAULT
#define CELL_DFLT_CHAR ' '
#define CELL_DFLT_FG COLOR_WHITE
#define CELL_DFLT_BG COLOR_BLACK
#define CELL_DFLT_ATTR A_NORMAL	//nessun attributo
#define CELL_NO_ATTR A_ATTRIBUTES


class Cell {
	private:
		char ch;	//char
		int fg, bg;	//colore testo / sfondo
		attr_t att;	//attributi

	public:
		Cell();											//inizializza con gli attributi di default
		Cell(char ch, int fg, int bg, attr_t att);		//valori minori di 0 (e CELL_NO_ATTR per att) inizializzano di default

		static void initPairs();						//da chiamare per inizializzare i color pair
		static int pairNumber(int fg, int bg);

		void edit(char ch, int fg, int bg, attr_t att);	//valori minori di 0 non modificano
		// GET
		char getCh();									//ritorna il carattere memorizzato
		int getBg();
		chtype toChtype() const;						//converte in unico valore chtype
		int pairNumber_own() const;						//ritorna il numero con cui è memorizzato il color_pair associato ai colori testo/sfondo dell'oggetto
		int colorPair() const;							//ritorna il color_pair associato ai colori testo/sfondo dell'oggetto
		/*
		essendoci solo 8 colori, le loro possibili combinazioni sono 8*8=64: dunque i numeri che identificano i color_pair possono essere inizializzati
		una volta per tutte secondo un certo ordine, e venire restituiti autonomamente dalla classe cell.
		**metodo di inizializzazione color_pair: nel caso specifico, per associare gli identificatori ai color_pair, utilizzo i numeri associati ad ogni colore
		(che vanno da 0 a 7) per memorizzarli in ordine, associando il colore 0 ai colori 0,1,..7, il colore 1 ai colori 0,1,..7 e così via.
		*/
};



#endif