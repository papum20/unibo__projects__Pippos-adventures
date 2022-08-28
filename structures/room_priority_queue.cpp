#include "room_priority_queue.hpp"



	RoomPriorityQueue::RoomPriorityQueue() : PriorityQueue() {
		RoomPriorityQueue(COMPARE_SIGN_DFLT);
	}
	RoomPriorityQueue::RoomPriorityQueue(int compareSign) : PriorityQueue(compareSign) {

	}


	void RoomPriorityQueue::insert(RoomPosition x) {
		if(!isFull()) {
			data[getSize()] = x;
			PriorityQueue::insert(&x);
		}
	}

	RoomPosition RoomPriorityQueue::random() {
		return data[rand() % getSize()];
	}
	RoomPosition RoomPriorityQueue::unevenRandom() {
		return data[getLinked(unevenRandom_index())];
	}