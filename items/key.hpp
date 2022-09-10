#ifndef KEY_HPP
#define KEY_HPP


#include "../artifact.hpp"


class Key : public Artifact {
    protected:

    public:
        Key();                   //ogni chiave apre solo una porta della stanza
};

typedef Key* pKey;

#endif
