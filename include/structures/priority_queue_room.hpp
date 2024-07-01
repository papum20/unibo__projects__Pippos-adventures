//// DA USARE COME PUNTATORE

#ifndef PRIORITY_QUEUE_ROOM_HPP
#define PRIORITY_QUEUE_ROOM_HPP


#include <iostream>
#include "main/definitions.hpp"
#include "structures/priority_queue.hpp"
#include "structures/room_position.hpp"




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
		int findPos(RoomPosition x);

		RoomPosition random();
		RoomPosition unevenRandom();

		// EREDITATI
		//int find(RoomPosition x, int i = 0);
		//void increaseKey(RoomPosition x, RoomPosition incr);

		
};
typedef PriorityQueue *pPriorityQueue;


#endif