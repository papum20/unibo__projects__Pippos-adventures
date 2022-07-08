#include "union_find.hpp"


UnionFind::UnionFind() {
	for(int i = 0; i < UNION_FIND_SIZE; i++) parent[i] = NULL;
}
void UnionFind::makeSet(s_coord s) {
	if(parent[s] == NULL) {
		parent[s] = new UFelement;
		parent[s]->val = s;
		parent[s]->weight = 1;
		parent[s]->parent = parent[s];
		parent[s]->next = NULL;
		//UFforest.insert(parent[s])
	}
}
s_coord UnionFind::find(s_coord s) {

}
void UnionFind::merge(s_coord a, s_coord b) {

}


//// GET
int UnionFind::getNumber() {
	return number;
}
s_coord UnionFind::getNth(int n) {
	if(n > number || n < 1) return -1;
	else {
		pUFforest p = sets;
		while(n > 1) {
			p = p->next;
			n--;
		}
		return p->tree->val;
	}
}
