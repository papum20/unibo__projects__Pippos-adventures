#ifndef NECKLACE_HPP
#define NECKLACE_HPP
#include <cstring> 
#include "item_difensivi.hpp"

const char necklace_description[description_length]="un tempo era il gioiello preferito dalla regina di Lyonesse, ora ha perso la lucentezza passata, pur mantenendo le proprietà magiche.";

class necklace: public item_difensivo{
    protected:

    public:
        necklace();
        necklace (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef necklace* pNecklace;

#endif