#ifndef DOOR_HPP
#define DOOR_HPP


#include "coordinate.hpp"
#include "inanimate.hpp"
#include "room.hpp"


class Door : public Inanimate {
	private:
		bool useable;
		//bool player_on;
		

	public:
		Door(Coordinate pos);
		void update();

		bool canUse();			//se si può cambiare stanza usandola
		//void setPlayerOn(bool p);
};

typedef Door *pDoor;



#endif