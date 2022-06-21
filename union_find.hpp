#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include "room.hpp"

#define UNION_FIND_SIZE (ROOM_WIDTH * ROOM_HEIGHT)


class UnionFind {
	private:
		int parents[UNION_FIND_SIZE];	//vettore dei padri: la cella di posizione i contiene il padre dell'elemento i
		int ranks[UNION_FIND_SIZE];		//ranghi: altezza del sottoalbero con radice il nodo i (=0 se il nodo non è inizializzato)
		int number;						//numero di insiemi
	public:
		UnionFind();
		void makeSet(int s);			//inizializza un insieme (singoletto) contenente s
		int find(int s);				//ritorna il rappresentante (radice dell'albero) di s
		void merge(int a, int b);		//unisce gli insiemi contenenti a e b

		//GET
		int getNumber();				//ritorna UnionFind.number
		int getNth(int n);				//ritorna l'n-esimo insieme (a partire da 1) (-1 se ci sono meno di n elementi)
};
typedef UnionFind *pUnionFind;





#endif