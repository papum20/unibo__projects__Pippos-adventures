#ifndef NECKLACE_HPP
#define NECKLACE_HPP
#include <cstring> 
#include "item_difensivi.hpp"

class Collana: public item_difensivi{
    protected:

    public:
        Collana (int dif, int d_mag, char rar[]);
};

#endif