#include "armor.hpp"

armor::armor():item_difensivo(){
    difesa_fisica_iniziale=0;Math::randomStep(5, 10, 5);
    difesa_magica_iniziale=0;Math::randomStep(10, 20, 5);
    strcpy (description, armor_description);
    strcpy (name, armor_name);
    apply_rarity();
}


char armor::get_type(){
    return ('a');
}