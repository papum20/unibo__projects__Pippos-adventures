#ifndef ROD_HPP
#define ROD_HPP
#include <cstring>
#include "weapon.hpp"

class Rod: public Weapon{
    protected:

    public:
        Rod();
        Rod (int d_f, int d_m, const char rar[], const char n[], const char desc[]);
};

#endif