#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP


#define UNION_FIND_SIZE (ROOM_WIDTH * ROOM_HEIGHT)


#include "coordinate.hpp"
#include "definitions.hpp"



class UnionFind {
	private:
		s_coord parents[UNION_FIND_SIZE];	//vettore dei padri: la cella di posizione i contiene il padre dell'elemento i
		int ranks[UNION_FIND_SIZE];			//ranghi: altezza del sottoalbero con radice il nodo i (=0 se il nodo non è inizializzato)
		int number;							//numero di insiemi
	public:
		UnionFind();
		void makeSet(s_coord s);			//inizializza un insieme (singoletto) contenente s
		s_coord find(s_coord s);			//ritorna il rappresentante (radice dell'albero) di s
		void merge(s_coord a, s_coord b);	//unisce gli insiemi contenenti a e b

		//GET
		int getNumber();					//ritorna UnionFind.number
		s_coord getNth(int n);				//ritorna l'n-esimo insieme (a partire da 1) (-1 se ci sono meno di n elementi)
		s_coord getNextInSet(s_coord current, s_coord parent);	//ritorna l'elemento successivo appartenente al set (in modo circolare, quindi alla fine ricomincia)
																//-1 se current non appartiene a parent o parent non è un rappresentante
};
typedef UnionFind *pUnionFind;





#endif