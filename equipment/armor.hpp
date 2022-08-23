#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring>
#include "item_difensivi.hpp" 

class armor: public item_difensivo{
    protected:

    public:
        armor (int dif, int d_mag, const char rar[], const char n[], const char desc[]);
    
        char get_type ();
};

typedef armor* pArmor;

#endif