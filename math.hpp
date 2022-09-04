#ifndef MATHS_HPP
#define MATHS_HPP

#include <iostream> 


//// MATH
class Math {
	public:
		static int abs(double n);		//valore assoluto
		static int ceil(double n);		//arrotondamento per eccesso
		static int randomStep (int min, int max, int step);
};


#endif