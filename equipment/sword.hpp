#ifndef SWORD_HPP
#define SWORD_HPP
#include <cstring>
#include "weapon.hpp" 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class sword: public Weapon{
    protected:

    public:
        sword (int d_f, int d_m, float v_a, char rar[], Character own);

        void apply_rune();
};

typedef sword* pSword;

#endif