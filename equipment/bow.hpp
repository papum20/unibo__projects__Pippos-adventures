#ifndef BOW_HPP
#define BOW_HPP
#include <cstring> 
#include "weapon.hpp"
#include "projectile.hpp"

class Arco: public Weapon{
    protected:
        Projectile freccia;
    public:
        Arco (int d_f, int d_m, float v_a, char rar[]);
};

#endif