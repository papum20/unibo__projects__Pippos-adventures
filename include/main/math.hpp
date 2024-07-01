#ifndef MATHS_HPP
#define MATHS_HPP

#include <iostream> 


//// MATH
class Math {
	public:
		static int abs(double n);		//valore assoluto
		static int floor(double n);		//piu gande intero minore o uguale
		static int ceil(double n);		//arrotondamento per eccesso
		static int randomStep (int min, int max, int step);
};


#endif