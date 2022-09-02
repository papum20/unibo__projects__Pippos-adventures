#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring>
#include "item_difensivi.hpp" 

const char armor_description[description_length]="Forgiata dalla dea Teti per suo figlio Achille, è ancora ricoperta del sangue delle vittime della funesta ira dell'eroe.";

class armor: public item_difensivo{
    protected:

    public:
        armor ();
        armor (int dif, int d_mag, const char rar[], const char n[], const char desc[]);
    
        char get_type ();
};

typedef armor* pArmor;

#endif