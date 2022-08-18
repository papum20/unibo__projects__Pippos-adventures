#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring>
#include "item_difensivi.hpp" 

class armor: public item_difensivi{
    protected:

    public:
        armor (int dif, int d_mag, char rar[]);
    
        char get_type ();
};

typedef armor* pArmor;

#endif