#ifndef INANIMATE_HPP
#define INANIMATE_HPP


#include "physical.hpp"






//classe parent di oggetti inanimati: wall, floor

class Inanimate : public Physical {
	protected:
		attr_t color;
		
	public:
		Inanimate();
		void init_colors();
};



#endif