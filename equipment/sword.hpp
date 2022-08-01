#ifndef SWORD_HPP
#define SWORD_HPP
#include <cstring>
#include "weapon.hpp" 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class Spada: public Weapon{
    protected:

    public:
        Spada (int d_f, int d_m, float v_a, char rar[], Character own);
};

#endif