#ifndef BOOTS_HPP
#define BOOTS_HPP
#include <cstring> 
#include "../item_difensivi.hpp"

const char boots_description[description_length]="Regalati da Ermes ad Autolico, permettono di muoversi leggiadri come il vento.";
const char boots_name[name_length]="Stivali di Ermes";

class boots: public item_difensivo{
    protected:

    public:
        boots();

        char get_type();
};

typedef boots* pBoots;

#endif