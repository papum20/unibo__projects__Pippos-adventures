#ifndef DOOR_HPP
#define DOOR_HPP

#include "physical.hpp"
#include "room.hpp"


class Door : public Physical {
	private:
		pRoom room;		//puntatore a stanza a cui collega
	public:
		Door(pRoom room);
};



#endif