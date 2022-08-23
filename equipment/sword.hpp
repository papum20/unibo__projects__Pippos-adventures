#ifndef SWORD_HPP
#define SWORD_HPP
#include <cstring>
#include "weapon.hpp" 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class sword: public Weapon{
    protected:

    public:
        sword (int d_f, int d_m, const char rar[], const char n[], const char desc[]);

        void apply_rune();
};

typedef sword* pSword;

#endif