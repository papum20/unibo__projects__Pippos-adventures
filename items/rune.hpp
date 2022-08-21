#ifndef RUNE_HPP
#define RUNE_HPP

#include "artifact.hpp"

class Rune: public Artifact{
    protected:

    public:
        Rune();

        void use_item (Weapon w);
        void use_item (Item_difensivo i_d);
};

typedef Rune* pRune;

#endif