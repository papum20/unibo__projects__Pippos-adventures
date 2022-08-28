#include "priority_queue_room.hpp"



	PriorityQueueRoom::PriorityQueueRoom() : PriorityQueue() {
		PriorityQueueRoom(COMPARE_SIGN_DFLT);
	}
	PriorityQueueRoom::PriorityQueueRoom(int compareSign) : PriorityQueue(compareSign) {

	}
	void PriorityQueueRoom::destroy() {
		PriorityQueue::destroy();
		for(int i = 0; i < getSize(); i++) delete data[i];
	}


	void PriorityQueueRoom::insert(RoomPosition x) {
		if(!isFull()) {
			data[getSize()] = new RoomPosition();
			data[getSize()]->copy(x);
			PriorityQueue::insert(data[getSize()]);
		}
	}
	void PriorityQueueRoom::remove(RoomPosition x) {
		int ind = find(x);
		if(ind != -1) {
			PriorityQueue::removeAt(ind);
			delete data[getSize() + 1];
		}
	}

	RoomPosition PriorityQueueRoom::random() {
		return *data[rand() % getSize()];
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
