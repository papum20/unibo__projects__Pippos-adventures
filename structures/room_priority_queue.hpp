#ifndef ROOM_PRIORITY_QUEUE_HPP
#define ROOM_PRIORITY_QUEUE_HPP


#include <iostream>
#include "definitions.hpp"
#include "priority_queue.hpp"
#include "room_position.hpp"


#define HEAP_SIZE_MAX ROOM_AREA		//deve contenere un "quadrato" di N_ROOMS e uno di ROOM_AREA
#define COMPARE_SIGN_DFLT -1		//min-heap
#define ROOM_RAND_EXECUTIONS_MAX 3	//massimo numero di esecuzioni di cicli che terminano solo in base a un numero random
#define ROOM_RAND_CHANCE 2			//usato come probabilità in generateMap()



class RoomPriorityQueue : public PriorityQueue {
	private:
		RoomPosition data[HEAP_SIZE_MAX];

	public:
		RoomPriorityQueue();
		RoomPriorityQueue(int compareSign);

		void insert(RoomPosition x);
		RoomPosition random();
		RoomPosition unevenRandom();

		// EREDITATI
		//void remove(RoomPosition x);
		//int find(RoomPosition x, int i = 0);
		//void increaseKey(RoomPosition x, RoomPosition incr);
};


#endif