#include "necklace.hpp"
#include <cstring>

necklace::necklace():item_difensivo(){
    difesa_fisica_iniziale=0;
    difesa_magica_iniziale=Math::randomStep(5, 10, 5);
    strcpy (description, necklace_description);
    apply_rarity();
}

char necklace::get_type(){
    return ('n');
}