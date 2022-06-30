#ifndef COORDINATE_HPP
#define COORDINATE_HPP


#include <iostream>



class Coordinate {
	public:
		int x, y;

		Coordinate();
		Coordinate(int x, int y);
		Coordinate(s_coord xy, int width);						//crea a partire da singola coordinata (vedi sotto)								

		bool inBounds(Coordinate mn, Coordinate mx);			//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		s_coord single(int width);								//converte in una singola coordinata, rispetto a una matrice finita (=y*width + x)
		void randomize(int xmin, int xmax, int ymin, int ymax);	//trasforma x e y in random (min inclusi, max esclusi)
																//se estremi uguali, non cambia il valore
};


typedef int s_coord;





#endif