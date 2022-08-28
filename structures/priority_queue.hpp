/*
	LE SOTTOCLASSI POSSONO MEMORIZZARE DATI AGGIUNTIVI DI ALTRO TIPO (CLASSE) USANDO UN ARRAY AGGIUNTIVO data[]
	CHE MEMORIZZA PUNTATORI AD ESSI
*/

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP


#include <iostream>
#include "comparable.hpp"
#include "definitions.hpp"
//#include "structure.hpp"


#define HEAP_SIZE_MAX ROOM_AREA			//deve contenere un "quadrato" di N_ROOMS e uno di ROOM_AREA
#define COMPARE_SIGN_DFLT -1			//min-heap
#define UNEVEN_RAND_EXECUTIONS_MAX 3	//massimo numero di esecuzioni di cicli che terminano solo in base a un numero random
#define UNEVEN_RAND_CHANCE 2			//usato come probabilità in generateMap()


class PriorityQueue {
	private:
		pComparable heap[HEAP_SIZE_MAX];
		//p_class data[HEAP_SIZE_MAX];		//array da definire nelle sottoclassi con eventuali dati aggiuntivi
		int size;
		int compareSign;					//risultato di compareTo, se applicato tra padre e figlio

		void fix(int i);

		int left(int i);					//figlio sinistro
		int right(int i);
		int parent(int i);


	protected:
		int unevenRandom_index();			//ritorna l'indice ottenuto con unevenRandom

		void removeAt(int ind);				//rimuove da un certo indice 
		virtual void swap(int a, int b);

		bool isFull();
		int getSize();

	public:
		PriorityQueue();
		PriorityQueue(int compareSign);
		void destroy();						//elimina tutti i puntatori

		void insert(pComparable x);
		void remove(Comparable x);			//se ce ne sono di più uguali, rimuove il primo che trova; fa anche il delete del puntatore
		void increaseKey(Comparable x, Comparable incr);
		int find(Comparable x, int i = 0);	//ritorna l'indice in heap, -1 se non trovato, il primo che trova se ce ne sono diversi

		Comparable random();				//ritorna un elemento random con uguali probabilità
		Comparable unevenRandom();			//random con probabilità diverse
};


#endif