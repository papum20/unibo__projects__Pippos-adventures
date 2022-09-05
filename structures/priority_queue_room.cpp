#include "priority_queue_room.hpp"



	PriorityQueueRoom::PriorityQueueRoom() : PriorityQueue(COMPARE_SIGN_DFLT) {
		
	}
	PriorityQueueRoom::PriorityQueueRoom(int compareSign) : PriorityQueue(compareSign) {

	}
	void PriorityQueueRoom::destroy() {
		PriorityQueue::destroy();
	}


	void PriorityQueueRoom::insert(RoomPosition x) {
		if(!isFull()) {
			data[size] = new RoomPosition();
			data[size]->copy(x);
			PriorityQueue::insert(data[size]);
		}
	}
	void PriorityQueueRoom::remove(RoomPosition x) {
		int ind = find(x);
		if(ind != -1) {
			PriorityQueue::removeAt(ind);
		}
	}

	RoomPosition PriorityQueueRoom::random() {
		return *data[rand() % size];
	}
	RoomPosition PriorityQueueRoom::unevenRandom() {
		return *data[unevenRandom_index()];
	}

//// AUSILIARIE
	void PriorityQueueRoom::swap(int a, int b) {
		PriorityQueue::swap(a, b);
		pRoomPosition tmp = data[a];
		data[a] = data[b];
		data[b] = tmp;
	}
