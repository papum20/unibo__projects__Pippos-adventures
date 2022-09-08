#ifndef MINIMAP_HPP
#define MINIMAP_CPP


#include "level.hpp"
#include "cell.hpp"


const Cell MINIMAP_ROOMS_BORDER = Cell('x', COLOR_WHITE, COLOR_BROWN, A_BOLD);
const Cell MINIMAP_ROOMS_EMPTY = Cell(' ', COLOR_WHITE, COLOR_GREEN, A_BOLD);
const Cell MINIMAP_ROOMS_PLAYER = Cell('P', COLOR_RED, COLOR_GREEN, A_BOLD);


class MiniMap {
	private:
		Coordinate position;
		Coordinate size;
		Coordinate padding;
		WINDOW *window;
		bool is_open;
	
		void drawLevel(pRoom rooms[LEVEL_AREA], Coordinate l_size, pRoom current);
		void drawRoom_in_level(pRoom room, Coordinate start, Coordinate size, bool current);

	public:
		MiniMap(int win_x, int win_y);
		void destroy();

		void open(Level level);
		void close();

		bool isOpen();
};




#endif