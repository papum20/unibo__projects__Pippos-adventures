#ifndef MINIMAP_HPP
#define MINIMAP_CPP


#include "cell.hpp"
#include "level.hpp"
#include "overlay.hpp"


const Cell MINIMAP_ROOMS_BORDER = Cell('x', COLOR_WHITE, COLOR_BROWN, A_BOLD);
const Cell MINIMAP_ROOMS_EMPTY = Cell(' ', COLOR_WHITE, COLOR_GREEN, A_BOLD);
const Cell MINIMAP_ROOMS_PLAYER = Cell('P', COLOR_RED, COLOR_GREEN, A_BOLD);
const Cell MINIMAP_ROOMS_BOSS = Cell('B', COLOR_RED, COLOR_GREEN, A_BOLD);


class MiniMap : public Overlay {
	private:
		pLevel level;
		Coordinate position;
		Coordinate size;
		Coordinate padding;
		bool is_open;
	
		void drawLevel(pRoom rooms[LEVEL_AREA], Coordinate l_size, pRoom current);
		void drawRoom_in_level(pRoom room, Coordinate start, Coordinate size, bool current);

	public:
		MiniMap(int win_x, int win_y, pLevel level);
		void destroy();

		void open();
		void close();

		bool isOpen();
		void setLevel(pLevel level);
};




#endif