//// PARENT DI FINESTRE, TIPO I MENU E LEVEL


#ifndef OVERLAY_HPP
#define OVERLAY_HPP


#include <curses.h>


class Overlay {
	protected:
		WINDOW *window;
		int width, height;
		bool is_open;
	public:
		Overlay();
		Overlay(int x, int y, int width, int height);
		virtual void destroy();

		virtual void open();				//apre sopra
		virtual void open_over(Overlay *B);	//chiama il close della finestra e apre questa
		virtual void close();
		bool isOpen();
};



#endif