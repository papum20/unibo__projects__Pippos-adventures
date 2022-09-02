#ifndef SHIELD_HPP
#define SHIELD_HPP

#include <cstring>
#include "../item_difensivi.hpp"

const char shield_description[description_length]="il possente scudo usato da Aiace, ha la resistenza di un intero castello.";

class shield: public item_difensivo{
    protected:

    public:
        shield();
        shield (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef shield* pShield;

#endif