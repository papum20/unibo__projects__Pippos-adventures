//// STRUTTURA DATI UNION-FIND CON IMPLEMENTAZIONE QUICK-FIND ED EURISTICA SUL PESO

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP


#include "../coordinate.hpp"
#include "../definitions.hpp"


#define UNION_FIND_SIZE (ROOM_AREA)


// ELEMENTI COME LISTE CIRCOLARI BIDIREZIONALI
struct UFelement {
	s_coord val;
	int weight;
	UFelement *parent;
	UFelement *next;
	UFelement *last;
};
typedef UFelement *pUFelement;



class UnionFind {
	private:
		pUFelement sets[UNION_FIND_SIZE];	//puntatori a set
		int number;							//numero di insiemi
	public:
		UnionFind();
		void destroy();
		
		void makeSet(s_coord s);			//inizializza un insieme (singoletto) contenente s
		s_coord find(s_coord s);			//ritorna il rappresentante (radice dell'albero) di s
		void merge(s_coord a, s_coord b);	//unisce gli insiemi contenenti a e b

		//GET
		s_coord next(s_coord set);			//permette di ottenere l'elemento successivo nel set, sffruttando l'implementazione a liste circolari, con il campo next di UFelement
		int getNumber();					//ritorna UnionFind.number
		s_coord firstSet();					//ritorna il padre del primo insieme memorizzato
};
typedef UnionFind *pUnionFind;





#endif