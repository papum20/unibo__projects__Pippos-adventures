#ifndef KEY_HPP
#define KEY_HPP

#include "artifact.hpp"

class Key: public item {
    protected:

    public:
        Key();                   //ogni chiave apre solo una porta della stanza

        void use_key();      //metodo a cui si passa l'id di una porta, se corrisponde ritorna true
};

typedef Key* pKey;

#endif
