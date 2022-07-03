#ifndef COORDINATE_HPP
#define COORDINATE_HPP


#include <iostream>


#define DFLT_COORDINATE_X 0
#define DFLT_COORDINATE_Y 0
#define DFLT_COORDINATE_W 1
#define DFLT_COORDINATE_H 1
#define DFLT_COORDINATE_SX 0
#define DFLT_COORDINATE_SY 0


typedef int s_coord;


class Coordinate {
	private:
		int startx, starty;
		int endx, endy;
	public:
		int x, y;

		Coordinate();
		Coordinate(int x, int y);
		Coordinate(int x, int y, int width, int height);
		Coordinate(int x, int y, int sx, int sy, int ex, int ey);
		Coordinate(s_coord xy, int width, int height);			//crea a partire da singola coordinata (vedi sotto)								
		Coordinate(const Coordinate a, const Coordinate b);		//crea come somma e matrice del primo

		//BOOL
		bool inBounds(Coordinate mn, Coordinate mx);			//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		bool inOwnBounds();
		//EDIT
		Coordinate times(int px, int py);						//x*px, y*py, modifica e ritorna
		Coordinate getTimes(int px, int py);					//ritorna solo il risultato
		void next();											//trasforma in coordinata successiva rispetto a matrice
		void randomize(int xmin, int xmax, int ymin, int ymax);	//trasforma x e y in random (min inclusi, max esclusi)
																//se estremi uguali, non cambia il valore

		//SET
		void setMatrix(int width, int height);					//non imposta se <=0
		void setFullMatrix(int sx, int sy, int ex, int ey);		//non imposta se <0 o start > end - 1
		//GET
		int relative_x();										//relativi alla matrice
		int relative_y();
		s_coord single();										//converte in una singola coordinata, rispetto a una matrice finita (=y*width + x)
};







#endif