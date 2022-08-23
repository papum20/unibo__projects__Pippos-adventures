#ifndef ROD_HPP
#define ROD_HPP
#include <cstring>
#include "weapon.hpp"

class Bastone_magico: public Weapon{
    protected:

    public:
        Bastone_Magico (int d_f, int d_m, const char rar[]);
};

#endif