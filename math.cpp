#include "math.hpp"


int Math::ceil(double n) {
	if(n < 0 || n - (int)n == 0) return n;
	else return n + 1;
}
