//// CLASSE PADRE CHE AMMETTE CONFRONTI

#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP


class Comparable {
	public:
		Comparable();
		int compareTo(Comparable B);	//1 se >B, 0 se =B, -1 se <B
		void add(Comparable B);			//somma a this B
};


#endif