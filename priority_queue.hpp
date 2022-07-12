#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP


#include "comparable.hpp"
#include "definitions.hpp"
#include "iostream"


#define HEAP_SIZE_MAX ROOM_AREA		//deve contenere un "quadrato" di N_ROOMS e uno di ROOM_AREA
#define COMPARE_SIGN_DFLT -1		//min-heap



class PriorityQueue {
	private:
		Comparable heap[HEAP_SIZE_MAX];
		int size;
		int compareSign;					//risultato di compareTo, se applicato tra padre e figlio

		int find(Comparable x, int i = 0);	//ritorna l'indice in heap, -1 se non trovato, il primo che trova se ce ne sono diversi
		void fix(int i);
		void swap(int a, int b);
		int left(int i);					//figlio sinistro
		int right(int i);
		int parent(int i);

	public:
		PriorityQueue();
		PriorityQueue(int compareSign);

		void insert(Comparable x);
		void remove(Comparable x);			//se ce ne sono di più uguali, rimuove il primo che trova
		void increaseKey(Comparable x, Comparable incr);

		Comparable random();				//ritorna un elemento random con uguali probabilità
		Comparable unevenRandom();			//random con probabilità diverse
};


#endif