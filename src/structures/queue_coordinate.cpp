#include "structures/queue_coordinate.hpp"


QueueCoordinate::QueueCoordinate() {
	head = NULL;
	tail = NULL;
	size = 0;
}
void QueueCoordinate::destroy() {
	while(head != NULL) {
		coord_pointer tmp = head;
		head = head->next;
		delete tmp;
	}
}

void QueueCoordinate::push(Coordinate c) {
	if(head == NULL) {
		head = new coord_pointer_t;
		tail = head;
	} else {
		tail->next = new coord_pointer_t;
		tail = tail->next;
	}
	tail->c = c;
	tail->next = NULL;
	size++;
}
Coordinate QueueCoordinate::pop() {
	coord_pointer tmp = head->next;
	Coordinate res = head->c;
	delete head;
	head = tmp;
	if(head == NULL) tail = NULL;
	size--;
	return res;
}

int QueueCoordinate::getSize() {
	return size;
}
bool QueueCoordinate::isEmpty() {
	return (size == 0);
}