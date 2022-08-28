#include "queue_coordinate.hpp"


Queue::Queue() {
	head = NULL;
	tail = NULL;
	size = 0;
}
void Queue::destroy() {
	while(head != NULL) {
		coord_pointer tmp = head;
		head = head->next;
		delete tmp;
	}
}

void Queue::push(Coordinate c) {
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
Coordinate Queue::pop() {
	coord_pointer tmp = head->next;
	Coordinate res = head->c;
	delete head;
	head = tmp;
	if(head == NULL) tail = NULL;
	size--;
	return res;
}

int Queue::getSize() {
	return size;
}
bool Queue::isEmpty() {
	return (size == 0);
}