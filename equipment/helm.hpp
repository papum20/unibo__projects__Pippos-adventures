#ifndef SHIELD_HPP
#define SHIELD_HPP
#include <cstring>
#include "../item_difensivi.hpp"

class helm: public item_difensivo{
    protected:

    public:
        helm();
        helm (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef helm* pHelm;

#endif