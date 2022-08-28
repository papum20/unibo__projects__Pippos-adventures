//// CLASSE PADRE CHE AMMETTE CONFRONTI

#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP


#include "object.hpp"


class Comparable : public Object {
	public:
		Comparable();
		Comparable(int unique_id);
		virtual int compareTo(Comparable B);	//1 se >B, 0 se =B, -1 se <B
		virtual void add(Comparable B);			//somma a this B
};
typedef Comparable *pComparable;


#endif