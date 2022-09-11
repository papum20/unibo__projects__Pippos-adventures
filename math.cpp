#include "math.hpp"



int Math::abs(double n) {
	if(n >= 0) return n;
	else return -n;
}
int Math::floor(double n) {
	if(n >= 0 || n + (int)n == 0) return n;
	else return n - 1;
}
int Math::ceil(double n) {
	if(n < 0 || n - (int)n == 0) return n;
	else return n + 1;
}

int Math::randomStep(int min, int max, int step){
	return ( (rand()%((max-min)/step+1))*step+min ); 
}