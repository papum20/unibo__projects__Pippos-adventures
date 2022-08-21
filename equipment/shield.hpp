#ifndef SHIELD_HPP
#define SHIELD_HPP
#include <cstring>
#include "item_difensivi" 

class shield: public item_difensivi{
    protected:

    public:
        Scudo (int dif, int d_mag, char rar[]);

        char get_type();
};

typedef shield* pShield;

#endif