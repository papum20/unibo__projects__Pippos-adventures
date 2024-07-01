#ifndef SHIELD_HPP
#define SHIELD_HPP

#include <cstring>
#include "../item_difensivi.hpp"

const char shield_description[description_length]="il possente scudo usato da Aiace, ha la resistenza di un intero castello.";
const char shield_name[name_length]="Scudo di Aiace";


class shield: public item_difensivo{
    protected:

    public:
        shield();

        char get_type();
};

typedef shield* pShield;

#endif