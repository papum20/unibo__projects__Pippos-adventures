#ifndef HELM_HPP
#define HELM_HPP

#include "../item_difensivi.hpp"

const char helm_description[description_length]="l'elmo del leggendario guerriero vichingo Lock Ragnak, chi lo indossa eredità le abilità del suo precedente possessore.";

class helm: public item_difensivo{
    protected:

    public:
        helm();
        helm (int dif, int d_mag, const char rar[], const char n[], const char desc[]);

        char get_type();
};

typedef helm* pHelm;

#endif