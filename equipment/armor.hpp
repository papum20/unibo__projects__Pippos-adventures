#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring>
#include "item_difensivi.hpp" 

class Armatura: public item_difensivi{
    protected:

    public:
        Armatura (int dif, int d_mag, char rar[]);
    
};

#endif