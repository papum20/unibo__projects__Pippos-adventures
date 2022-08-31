#ifndef BOOTS_HPP
#define BOOTS_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class boots: public item_difensivo{
    protected:

    public:
        boots();
        boots (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef boots* pBoots;

#endif