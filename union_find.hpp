//// STRUTTURA DATI UNION-FIND CON IMPLEMENTAZIONE QUICK-FIND ED EURISTICA SUL PESO

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP


#include "coordinate.hpp"
#include "definitions.hpp"


#define UNION_FIND_SIZE (ROOM_WIDTH * ROOM_HEIGHT)


// ELEMENTI COME LISTE CIRCOLARI
struct UFelement {
	s_coord val;
	int weight;
	UFelement *parent;
	UFelement *next;
};
typedef UFelement *pUFelement;


/*struct UFforest {
	pUFelement tree;
	UFforest *next;
};
typedef UFforest *pUFforest;*/





class UnionFind {
	private:
		pUFelement sets[UNION_FIND_SIZE];	//puntatori a set
		//pUFforest sets;					//insiemi (foresta di alberi di altezza 1)
		int number;							//numero di insiemi
	public:
		UnionFind();
		void makeSet(s_coord s);			//inizializza un insieme (singoletto) contenente s
		s_coord find(s_coord s);			//ritorna il rappresentante (radice dell'albero) di s
		void merge(s_coord a, s_coord b);	//unisce gli insiemi contenenti a e b

		//GET
		int getNumber();					//ritorna UnionFind.number
		s_coord firstSet();					//ritorna il padre del primo insieme memorizzato
		//s_coord getNth(int n);				//ritorna l'n-esimo insieme (a partire da 1) (-1 se ci sono meno di n elementi)
		//s_coord getNextInSet(s_coord current, s_coord parent);	//ritorna l'elemento successivo appartenente al set (in modo circolare, quindi alla fine ricomincia)
																//-1 se current non appartiene a parent o parent non è un rappresentante
};
typedef UnionFind *pUnionFind;





#endif