#include "room_position.hpp"


	RoomPosition::RoomPosition() : Comparable() {
		RoomPosition(Coordinate(-1, -1), 0);
	}
	RoomPosition::RoomPosition(Coordinate pos, int connected) : Comparable() {
		this->pos = pos;
		this->connected = connected;
	}
	void RoomPosition::copy(RoomPosition rp) {
		pos = rp.pos;
		connected = rp.connected;
	}
		
	int RoomPosition::compareTo(RoomPosition B) {
		if(connected > B.connected) return 1;
		else if(connected == B.connected) return 0;
		else return -1;
	}
	void RoomPosition::add(RoomPosition B) {
		connected += B.connected;
	}

	Coordinate RoomPosition::getPos() {
		return pos;
	}