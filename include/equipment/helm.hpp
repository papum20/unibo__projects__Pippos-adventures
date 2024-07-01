#ifndef HELM_HPP
#define HELM_HPP

#include "main/item_difensivi.hpp"

const char helm_description[description_length]="l'elmo del leggendario guerriero vichingo Lock Ragnak, chi lo indossa eredita le abilita' del suo precedente possessore.";
const char helm_name[name_length]="Elmo di Ragnak";

class helm: public item_difensivo{
    protected:

    public:
        helm();

        char get_type();
};

typedef helm* pHelm;

#endif