#ifndef SYSTEM_TEXT_HPP
#define SYSTEM_TEXT_HPP



#include <curses.h>
#include <iostream>
#include "pixel_art.hpp"
#include "definitions.hpp"
#include <cstring>

#define WINDOW_TEXT_HEIGHT 13
#define WINDOW_TEXT_WIDTH 70



class System_text {
	protected:
    WINDOW * text;
    int space;
    int text_x_pos, text_y_pos;
    bool is_open;
	public:
		System_text(int stdscr_x, int stdscr_y);
        void destroy();
        bool is_active();
        void open();
        void close();
        void insert_string(const char string[]);
        void clean_window(WINDOW* window, int w_hight, int w_lenght);
};



#endif
