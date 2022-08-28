#ifndef QUEUE_HPP
#define QUEUE_HPP


struct queue_coord {
	Coord c;
	queue_coord *next;
};
typedef queue_coord *p_queue_coord;

class Queue {
	private:
		p_queue_coord head;
		p_queue_coord tail;
		int size;
	public:
		Queue() {
			head = tail = NULL;
			size = 0;
		}
		void push(Coord c) {
			if(head == NULL) {
				head = new queue_coord;
				tail = head;
			} else {
				tail->next = new queue_coord;
				tail = tail->next;
			}
			tail->c = c;
			tail->next = NULL;
			size++;
		}
		Coord pop() {
			p_queue_coord tmp = head->next;
			Coord res = head->c;
			delete head;
			head = tmp;
			if(head == NULL) tail = NULL;
			size--;
			return res;
		}
		int getSize() {
			return size;
		}
		bool isEmpty() {
			return (size == 0);
		}
		void erase() {
			while(head != NULL) {
				p_queue_coord tmp = head;
				head = head->next;
				delete tmp;
			}
		}
		void print() {
			cout << endl;
			p_queue_coord p = head;
			while(p != NULL) {
				printf("%d,%d ", p->c.x, p->c.y);
				p = p->next;
			}
			cout << endl;
		}
};


#endif