//// DA USARE COME PUNTATORE

#ifndef PRIORITY_QUEUE_ROOM_HPP
#define PRIORITY_QUEUE_ROOM_HPP


#include <iostream>
#include "definitions.hpp"
#include "priority_queue.hpp"
#include "room_position.hpp"


#define HEAP_SIZE_MAX ROOM_AREA		//deve contenere un "quadrato" di N_ROOMS e uno di ROOM_AREA
#define COMPARE_SIGN_DFLT -1		//min-heap
#define ROOM_RAND_EXECUTIONS_MAX 3	//massimo numero di esecuzioni di cicli che terminano solo in base a un numero random
#define ROOM_RAND_CHANCE 2			//usato come probabilità in generateMap()



class PriorityQueueRoom : public PriorityQueue {
	private:
		pRoomPosition data[HEAP_SIZE_MAX];

		void swap(int a, int b);

	public:
		PriorityQueueRoom();
		PriorityQueueRoom(int compareSign);
		void destroy();

		void insert(RoomPosition x);
		void remove(RoomPosition x);

		RoomPosition random();
		RoomPosition unevenRandom();

		// EREDITATI
		//int find(RoomPosition x, int i = 0);
		//void increaseKey(RoomPosition x, RoomPosition incr);
};
typedef PriorityQueue *pPriorityQueue;


#endif