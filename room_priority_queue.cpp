#include "room_priority_queue.hpp"



	RoomPriorityQueue::RoomPriorityQueue() {
		RoomPriorityQueue(COMPARE_SIGN_DFLT);
	}
	RoomPriorityQueue::RoomPriorityQueue(int compareSign) {
		size = 0;
		this->compareSign = compareSign;
	}


//// PRINCIPALI
#pragma region HEAP_PRINCIPALI
	void RoomPriorityQueue::insert(RoomPosition x) {
		if(size < HEAP_SIZE_MAX) {
			heap[size] = x;
			fix(size);
			size++;
		}
	}
	void RoomPriorityQueue::remove(RoomPosition x) {
		int ind = find(x);
		if(ind != -1) {
			swap(ind, size - 1);
			size--;
			fix(ind);
		}
	}
	void RoomPriorityQueue::increaseKey(RoomPosition x, RoomPosition incr) {
		int ind = find(x);
		if(ind != -1) {
			x.add(incr);
			fix(ind);
		}
	}

	RoomPosition RoomPriorityQueue::random() {
		return heap[rand() % size];
	}
	RoomPosition RoomPriorityQueue::unevenRandom() {
		int i = 0;
		int executions = ROOM_RAND_EXECUTIONS_MAX;
		do {	//verrebbe comunque eseguito almeno una volta anche con il while
			if(rand() % ROOM_RAND_CHANCE == 0) executions = 0;
			else {
				if(left(i) < size && rand() % 2) i = left(i);
				else if(right(i) < size) i = right(i);
				else {
					i = 0;
					executions--;
				}
			}
		} while(executions > 0);
		return heap[i];
	}

#pragma endregion HEAP_PRINCIPALI


#pragma region HEAP_AUSILIARIE
	int RoomPriorityQueue::find(RoomPosition x, int i) {
		if(i >= size) return -1;
		else {
			if(heap[i].compareTo(x) == 0) return i;
			else {
				int l = find(x, left(i));
				if(l != -1) return l;
				else return find(x, right(i));
			}
		}
	}
	void RoomPriorityQueue::fix(int i) {
		if(size > 0) {
			//controlla su
			while(i > 0 && heap[parent(i)].compareTo(heap[i]) == compareSign) {
				swap(i, parent(i));
				i = parent(i);
			}
			//controlla giu
			while( (left(i) < size && heap[i].compareTo(heap[left(i)]) == compareSign) || (right(i) < size && heap[i].compareTo(heap[right(i)]) == compareSign) ) {
				if(right(i) >= size || heap[i].compareTo(heap[left(i)]) == compareSign) i = left(i);
				else i = right(i);
				swap(i, parent(i));
			}
		}
	}
	void RoomPriorityQueue::swap(int a, int b) {
		RoomPosition tmp = heap[a];
		heap[a] = heap[b];
		heap[b] = tmp;
	}
	int RoomPriorityQueue::left(int i) {
		return i * 2 + 1;
	}
	int RoomPriorityQueue::right(int i) {
		return i * 2 + 2;
	}
	int RoomPriorityQueue::parent(int i) {
		return (i - 1) / 2;
	}
#pragma endregion HEAP_AUSILIARIE