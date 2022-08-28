//// CLASSE PADRE PER OGGETTI, USABILI IN STRUTTURE

#ifndef OBJECT_HPP
#define OBJECT_HPP


#define DFLT_UNIQUE_ID 0


class Object {
	private:
		int unique_id;
	public:
		Object();
		Object(int unique_id);
		int getUniqueId();
};


#endif