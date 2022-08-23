#ifndef BOOTS_HPP
#define BOOTS_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class boots: public item_difensivi{
    protected:

    public:
        boots (int dif, int d_mag, const char rar[]);

        char get_type();
};

typedef boots* pBoots;

#endif