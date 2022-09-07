#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring>
#include "../item_difensivi.hpp" 

const char armor_description[description_length]="Forgiata dalla dea Teti per suo figlio Achille, è ancora ricoperta del sangue delle vittime della funesta ira dell'eroe.";
const char armor_name[name_length]="Armatura di Achille";

class armor: public item_difensivo{
    protected:

    public:
        armor ();
    
        char get_type ();
};

typedef armor* pArmor;

#endif