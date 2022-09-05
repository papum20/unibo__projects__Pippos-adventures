//// CLASSE CHE MEMORIZZA UNA COORDINATA, COME COPPIA X,Y (float), ED EVENTUALI "CONFINI" DI UNA MATRICE DA CUI NON PUÒ USCIRE E DI PIÙ INTERNI PER CONTROLLI E next (estremi finali escluso)
//// PERMETTE DI VERIFICARE SE LE COORDINATE SI TROVINO IN TALI BORDI (INTERNI) CON inBounds() e inOwnBounds(),
//// E DI OTTENERE UNA COORDINATA "SINGOLA", RELATIVA AI BORDI, UTILIZZABILE COME INDICE, CON single() (sempre grazie ai confini interni)
//// IMPLEMENTA SVARIATE SEMPLICI OPERAZIONI

#ifndef COORDINATE_HPP
#define COORDINATE_HPP


#include <iostream>
#include "math.hpp"
#include "definitions.hpp"


#define DFLT_COORDINATE_X 0
#define DFLT_COORDINATE_Y 0
#define DFLT_COORDINATE_SX 0
#define DFLT_COORDINATE_SY 0
#define DFLT_COORDINATE_W 1
#define DFLT_COORDINATE_H 1


typedef int s_coord;				//tipo per una coordinata singola


class Coordinate {
	private:
		//DIMENSIONI IN CUI DEVE ESSERE COMPRESA (minimo=(0,0), massimo=size)
		float sizex, sizey;
		//DIMENSIONI (SOTTOINSIEME DI SIZE) IN CUI SI POSSONO FARE CONTROLLI CON InOwnBounds E PER USARE NEXT
		//RIMANGONO UGUALI ALLA MATRICE FINCHÉ NON VENGONO IMPOSTATI
		float startx, starty;		//estremo incluso
		float endx, endy;			//estremo escluso
	public:
		float x, y;

		Coordinate();																	//x,y = 0,0
		Coordinate(float x, float y);													//estremi: 0,0; 1,1
		Coordinate(float x, float y, Coordinate size);									//estremi: 0,0; size
		Coordinate(Coordinate pos, Coordinate start, Coordinate end);					//size=end
		Coordinate(Coordinate pos, Coordinate size, Coordinate start, Coordinate end);	//dichiarazione completa, con tutti gli estremi
		Coordinate(s_coord xy, Coordinate size);										//crea a partire da singola coordinata						
		Coordinate(const Coordinate a, const Coordinate b);								//crea come somma e con estremi del primo

		static Coordinate unitVector(Coordinate A, Coordinate B);		//ritorna il vettore da A a B con coordinata maggiore=1 (in valore assoluto) (e minore tra -1 e 1)

		//BOOL
		bool inBounds(Coordinate mn, Coordinate mx);					//ritorna true se xmin<=x<xmax && ymin<=y<ymax
		bool inOwnBounds();
		bool equals(Coordinate B) const;								//se hanno stessi x e y
		bool equals_int(Coordinate B) const;							//equals, ma confronta la parte intera
		bool lessEqual(Coordinate B);									//x<B.x && yB.y
		//EDIT
		Coordinate negative() const;									//return (-x, -y)
		Coordinate times(float px, float py);							//return (x*px, y*py)
		void clamp(Coordinate mn, Coordinate mx);						//fa rientrare le coordinate nei bordi (mn lessEqual mx)
		void next();													//trasforma in coordinata successiva rispetto a matrice (incrementata di 1, non esce fuori dai bordi, se arrivato alla fine diventa l'inizio della matrice); funziona solo con matrice impostata (o ritorna ERROR_INT)
		void randomize(int xmin, int xmax, int ymin, int ymax);			//trasforma x e y in random (min inclusi, max esclusi) (solo interi)
																		//se estremi uguali, non cambia il valore
		//SET
		void setMatrix(Coordinate size);								//imposta la matrice esterna (valori entrambi >0)
		void setBounds(Coordinate start, Coordinate end);				//imposta i confini interni; si può usare un qualsiasi rettangolo, con vertici qualsiasi; arrotonda un bound alla matrice se ne uscirebbe fuori
		//GET
		Coordinate size() const;
		Coordinate start() const;
		Coordinate end() const;
		int intx() const;								//coordinate intere
		int inty() const;
		int ceilx();									//coordinate intere (arrotondate per eccesso)
		int ceily();
		Coordinate relative();							//relativi alla matrice
		int rel_int_x();								//relativi alla matrice (intero)
		int rel_int_y();
		s_coord single();								//converte in una singola coordinata, rispetto a una matrice finita (=y*width + x) (usa parte intera delle coordinate); funziona solo con matrice impostata (o ritorna ERROR_INT)
		s_coord single_ceil();							//single (usa arrotondamenti per eccesso delle coordinate)
};


const Coordinate COORDINATE_ZERO = Coordinate(0, 0);
const Coordinate COORDINATE_ONE = Coordinate(1, 1);
const Coordinate COORDINATE_NEGATIVE = Coordinate(-1, -1);
const Coordinate COORDINATE_ERROR = COORDINATE_NEGATIVE;		//COORDINATA DI RITORNO "DI ERRORE"

//// DIREZIONI
//direzioni (vettori unitari) (utili per la generazione di stanze e livelli)
#define DIRECTIONS_N 4
//define DIR_COORD 2
#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
const Coordinate DIRECTIONS[DIRECTIONS_N] = {Coordinate(0,1), Coordinate(1,0), Coordinate(0,-1), Coordinate(-1,0)};	//up, right, down, left


#endif