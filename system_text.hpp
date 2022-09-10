#ifndef SYSTEM_TEXT_HPP
#define SYSTEM_TEXT_HPP



#include <curses.h>
#include <iostream>
#include "pixel_art.hpp"

#define WINDOW_TEXT_HEIGHT 13
#define WINDOW_TEXT_WIDTH 50




class System_text {
	protected:
    WINDOW * text;
    int space;
    int text_x_pos, text_y_pos;
    bool is_open;
    bool is_full;
	public:
		System_text(int stdscr_x, int stdscr_y);
        void destroy();
        bool is_active();
        void open();
        void close();
        void insert_string(const char string[]);
        void insert_number(const char string[]);
};



#endif
