#include "priority_queue.hpp"



	PriorityQueue::PriorityQueue() {
		PriorityQueue(COMPARE_SIGN_DFLT);
	}
	PriorityQueue::PriorityQueue(int compareSign) {
		size = 0;
		this->compareSign = compareSign;
	}


//// PRINCIPALI
#pragma region HEAP_PRINCIPALI
	void PriorityQueue::insert(Comparable x) {
		if(size < HEAP_SIZE_MAX) {
			heap[size] = x;
			fix(size);
			size++;
		}
	}
	void PriorityQueue::remove(Comparable x) {
		int ind = find(x);
		if(ind != -1) {
			swap(ind, size - 1);
			size--;
			fix(ind);
		}
	}
	void PriorityQueue::increaseKey(Comparable x, Comparable incr) {
		int ind = find(x);
		if(ind != -1) {
			x.add(incr);
			fix(ind);
		}
	}

	Comparable PriorityQueue::random() {
		return heap[rand() % size];
	}
	Comparable PriorityQueue::unevenRandom() {

	}
#pragma endregion HEAP_PRINCIPALI


#pragma region HEAP_AUSILIARIE
	int PriorityQueue::find(Comparable x, int i = 0) {
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
	void PriorityQueue::fix(int i) {
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
	void PriorityQueue::swap(int a, int b) {
		Comparable tmp = heap[a];
		heap[a] = heap[b];
		heap[b] = tmp;
	}
	int PriorityQueue::left(int i) {
		return i * 2 + 1;
	}
	int PriorityQueue::right(int i) {
		return i * 2 + 2;
	}
	int PriorityQueue::parent(int i) {
		return (i - 1) / 2;
	}
#pragma endregion HEAP_AUSILIARIE