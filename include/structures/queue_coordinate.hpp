//// STRUTTURA FIFO (FIRST IN FIRST OUT)

#ifndef QUEUE_COORDINATE_HPP
#define QUEUE_COORDINATE_HPP


#include "main/coordinate.hpp"


struct coord_pointer_t {
	Coordinate c;
	coord_pointer_t *next;
};
typedef coord_pointer_t *coord_pointer;


class QueueCoordinate {
	private:
		coord_pointer head;
		coord_pointer tail;
		int size;

	public:
		QueueCoordinate();
		void destroy();				//fa il delete di tutti i puntatori

		void push(Coordinate c);	//inserisce
		Coordinate pop();			//rimuove e ritorna il primo inserito
		
		int getSize();
		bool isEmpty();
};


#endif