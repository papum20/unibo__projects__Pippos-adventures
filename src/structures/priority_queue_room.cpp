#include "structures/priority_queue_room.hpp"


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
		int ind = findPos(x);
		if(ind != -1) {
			PriorityQueue::removeAt(ind);
		}
	}
	int PriorityQueueRoom::findPos(RoomPosition x) {
		int res = -1;
		int i = 0;
		while(res == -1 && i < size) {
			if(data[i]->getPos().equals((x.getPos()))) res = i;
			else i++;
		}
		return res;
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
