#ifndef RUNE_HPP
#define RUNE_HPP

#include "../artifact.hpp"

const char rune_description[description_length]="Runa magica molto potente capace di aumentare la rarita' di un oggetto random equipaggiato";
const char rune_name[name_length]="Runa magica";

class Rune: public Artifact{
    protected:

    public:
        Rune();

        void use_rune (pItem item);
        void use_item (pItem item, int &stat, System_text* text);
};

typedef Rune* pRune;

#endif