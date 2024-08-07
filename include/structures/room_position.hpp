#ifndef ROOM_POSITION_HPP
#define ROOM_POSITION_HPP


#include "main/coordinate.hpp"
#include "structures/comparable.hpp"


class RoomPosition : public Comparable {
	private:
		Coordinate pos;
		int connected;
	public:
		RoomPosition();
		RoomPosition(Coordinate pos, int connected);
		void copy(RoomPosition rp);
		
		int compareTo(RoomPosition B);	//1 se >B, 0 se =B, -1 se <B
		void add(RoomPosition B);		//somma a this B

		Coordinate getPos();
		int getConnected();
};
typedef RoomPosition *pRoomPosition;



#endif