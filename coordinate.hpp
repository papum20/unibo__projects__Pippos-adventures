//// CLASSE CHE MEMORIZZA UNA COORDINATA, COME COPPIA X,Y, ED EVENTUALI "CONFINI" DI UNA MATRICE
//// PERMETTE DI VERIFICARE SE LE COORDINATE SI TROVINO IN TALI BORDI CON inBounds() e inOwnBounds(),
//// E DI OTTENERE UNA COORDINATA "SINGOLA", RELATIVA AI BORDI, UTILIZZABILE COME INDICE, CON single()



#ifndef COORDINATE_HPP
#define COORDINATE_HPP


#include <iostream>
#include "math.hpp"


#define DFLT_COORDINATE_X 0
#define DFLT_COORDINATE_Y 0
#define DFLT_COORDINATE_SX 0
#define DFLT_COORDINATE_SY 0
#define DFLT_COORDINATE_W 1
#define DFLT_COORDINATE_H 1


typedef int s_coord;				//tipo per una coordinata singola


class Coordinate {
	private:
		float startx, starty;		//estremo incluso
		float endx, endy;			//estremo escluso
	public:
		float x, y;

		Coordinate();													//x,y = 0,0
		Coordinate(float x, float y);									//estremi: 0,0; 1,1
		Coordinate(float x, float y, Coordinate size);					//estremi: 0,0; size
		Coordinate(Coordinate pos, Coordinate start, Coordinate end);	//dichiarazione completa, con tutti gli estremi
		Coordinate(s_coord xy, Coordinate size);						//crea a partire da singola coordinata						
		Coordinate(const Coordinate a, const Coordinate b);				//crea come somma e con estremi del primo

		//BOOL
		bool inBounds(Coordinate mn, Coordinate mx);					//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		bool inOwnBounds();
		//bool inBoundsX(float xmin, float xmax);						//se x compreso, estremi inclusi
		//bool inBoundsY(float ymin, float ymax);
		bool equals(Coordinate B);										//se hanno stessi x e y
		bool equals_int(Coordinate B);									//equals, ma confronta la parte intera
		bool lessEqual(Coordinate B);									//se x e y < B.x e B.y
		//bool equalsDirection(Coordinate B);							//se hanno la stessa direzione
		//EDIT
		Coordinate negative();											//modifica e ritorna l'opposto (-x, -y)
		Coordinate getNegative() const;									//ritorna l'opposto (-x, -y)
		Coordinate times(float px, float py);							//x*px, y*py, modifica e ritorna
		Coordinate getTimes(float px, float py);						//ritorna solo il risultato
		void next();													//trasforma in coordinata successiva rispetto a matrice
		void randomize(int xmin, int xmax, int ymin, int ymax);			//trasforma x e y in random (min inclusi, max esclusi) (solo interi)
																		//se estremi uguali, non cambia il valore

		//SET
		void setMatrix(Coordinate size);								//imposta l'estremo finale come estremo iniziale + size; non imposta una coordinata se <=0 (può anche impostarne solo una)
		void setFullMatrix(Coordinate start, Coordinate end);			//si può usare un qualsiasi rettangolo, con vertici qualsiasi; non imposta se <0(imposta solo i valori validi)
		//GET
		int intx();										//coordinate intere
		int inty();
		int ceilx();									//coordinate intere (arrotondate per eccesso)
		int ceily();
		float relative_x();								//relativi alla matrice
		float relative_y();
		s_coord single();								//converte in una singola coordinata, rispetto a una matrice finita (=y*width + x) (usa parte intera delle coordinate)
		s_coord single_ceil();							//single (usa arrotondamenti per eccesso delle coordinate)
};



const Coordinate COORDINATE_ERROR = Coordinate(-1, -1);		//COORDINATA DI RITORNO "DI ERRORE"


#endif