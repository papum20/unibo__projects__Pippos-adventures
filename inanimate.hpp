#ifndef INANIMATE_HPP
#define INANIMATE_HPP


#include "physical.hpp"






//classe parent di oggetti inanimati: wall, floor

class Inanimate : public Physical {
	protected:
		attr_t main_color;
		attr_t second_color;
		
	public:
		Inanimate();
		void init_colors();

		void drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos, attr_t color);	//overridden
};



#endif