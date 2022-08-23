#ifndef NECKLACE_HPP
#define NECKLACE_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class necklace: public item_difensivo{
    protected:

    public:
        necklace (int dif, int d_mag, const char rar[]);

        char get_type();
};

typedef necklace* pNecklace;

#endif