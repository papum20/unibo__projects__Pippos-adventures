#ifndef RUNE_HPP
#define RUNE_HPP

#include "../artifact.hpp"

class Rune: public Artifact{
    protected:

    public:
        Rune();
        Rune(const char n[], const char desc[]);

        void use_rune (Weapon w);
        void use_rune (item_difensivo i_d);
        void use_item (pPlayer);
};

typedef Rune* pRune;

#endif