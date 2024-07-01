#ifndef KEY_HPP
#define KEY_HPP



#include "main/item.hpp"



class Key : public item {
    protected:

    public:
        Key();                   //ogni chiave apre solo una porta della stanza
};

typedef Key* pKey;

#endif
