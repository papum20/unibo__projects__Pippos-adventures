#ifndef NECKLACE_HPP
#define NECKLACE_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class necklace: public item_difensivo{
    protected:

    public:
        necklace();
        necklace (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef necklace* pNecklace;

#endif