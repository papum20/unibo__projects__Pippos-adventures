#ifndef BOOTS_HPP
#define BOOTS_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class Stivali: public item_difensivi{
    protected:

    public:
        Stivali (int dif, int d_mag, char rar[]);
};

#endif