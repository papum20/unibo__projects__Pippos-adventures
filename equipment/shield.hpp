#ifndef SHIELD_HPP
#define SHIELD_HPP
#include <cstring>
#include "item_difensivi" 

class Scudo: public item_difensivi{
    protected:

    public:
        Scudo (int dif, int d_mag, char rar[]);
};

#endif