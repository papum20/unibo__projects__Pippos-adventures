#include "necklace.hpp"
#include <cstring>

necklace::necklace():item_difensivo(){
    strcpy(rarity, epic);
    id=ID_ITEM_DIFENSIVO_NECKLACE;
    difesa_fisica_iniziale=0;
    difesa_magica_iniziale=Math::randomStep(5, 10, 5);
    strcpy (description, necklace_description);
    strcpy (name, necklace_name);
    apply_rarity();
}

char necklace::get_type(){
    return ('n');
}