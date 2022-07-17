#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "inanimate.hpp"


class Door : public Inanimate {
	private:

	public:
		Door(Coordinate pos);
};

typedef Door *pDoor;



#endif