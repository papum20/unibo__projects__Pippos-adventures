#ifndef ROOM_H
#define ROOM_H


#include "character.hpp"




class Room {
	private:
		
	public:
		Room();

		bool checkMovement(int x, int y);
		Character checkCharacter(int x, int y);
};






#endif