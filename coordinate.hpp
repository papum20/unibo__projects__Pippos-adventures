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
		float startx, starty;
		float endx, endy;
	public:
		float x, y;

		Coordinate();
		Coordinate(float x, float y);
		Coordinate(float x, float y, Coordinate size);
		Coordinate(float x, float y, float sx, float sy, float ex, float ey);
		Coordinate(s_coord xy, Coordinate size);					//crea a partire da singola coordinata (vedi sotto)								
		Coordinate(const Coordinate a, const Coordinate b);			//crea come somma e matrice del primo

		//BOOL
		bool inBounds(Coordinate mn, Coordinate mx);			//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		bool inOwnBounds();
		//bool inBoundsX(float xmin, float xmax);					//se x compreso, estremi inclusi
		//bool inBoundsY(float ymin, float ymax);
		bool equals(Coordinate B);
		//bool equalsDirection(Coordinate B);					//se hanno la stessa direzione
		//EDIT
		Coordinate negative();									//modifica e ritorna l'opposto
		Coordinate getNegative();
		void sum(Coordinate B);
		Coordinate times(float px, float py);					//x*px, y*py, modifica e ritorna
		Coordinate getTimes(float px, float py);				//ritorna solo il risultato
		void next();											//trasforma in coordinata successiva rispetto a matrice
		void randomize(int xmin, int xmax, int ymin, int ymax);	//trasforma x e y in random (min inclusi, max esclusi) (solo interi)
																//se estremi uguali, non cambia il valore

		//SET
		void setMatrix(Coordinate size);								//non imposta se <=0
		void setFullMatrix(float sx, float sy, float ex, float ey);		//non imposta se <0 o start > end - 1
		//GET
		int intx();										//coordinate intere
		int inty();
		float relative_x();										//relativi alla matrice
		float relative_y();
		s_coord single();										//converte in una singola coordinata, rispetto a una matrice finita (=y*width + x)
};







#endif