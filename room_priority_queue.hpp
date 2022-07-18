#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP


#include "definitions.hpp"
#include "iostream"
#include "room_position.hpp"


#define HEAP_SIZE_MAX ROOM_AREA		//deve contenere un "quadrato" di N_ROOMS e uno di ROOM_AREA
#define COMPARE_SIGN_DFLT -1		//min-heap
#define ROOM_RAND_EXECUTIONS_MAX 3	//massimo numero di esecuzioni di cicli che terminano solo in base a un numero random
#define ROOM_RAND_CHANCE 2			//usato come probabilità in generateMap()



class RoomPriorityQueue {
	private:
		RoomPosition heap[HEAP_SIZE_MAX];
		int size;
		int compareSign;					//risultato di compareTo, se applicato tra padre e figlio

		void fix(int i);
		void swap(int a, int b);
		int left(int i);					//figlio sinistro
		int right(int i);
		int parent(int i);

	public:
		RoomPriorityQueue();
		RoomPriorityQueue(int compareSign);

		void insert(RoomPosition x);
		void remove(RoomPosition x);			//se ce ne sono di più uguali, rimuove il primo che trova
		int find(RoomPosition x, int i = 0);	//ritorna l'indice in heap, -1 se non trovato, il primo che trova se ce ne sono diversi
		void increaseKey(RoomPosition x, RoomPosition incr);

		RoomPosition random();					//ritorna un elemento random con uguali probabilità
		RoomPosition unevenRandom();			//random con probabilità diverse
};


#endif