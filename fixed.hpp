//// CLASSE PARENT DI OGGETTI FERMI E NON ATTRAVERSABILI/NON MOVIBILI (WALL E DOOR)


#ifndef FIXED_HPP
#define FIXED_HPP


#include "inanimate.hpp"


class Fixed : public Inanimate {
	protected:
		int height;
	
	public:
		Fixed();
};





#endif