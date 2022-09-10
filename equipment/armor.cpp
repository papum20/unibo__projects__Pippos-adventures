#include "armor.hpp"

armor::armor():item_difensivo(){
    //strcpy(rarity, rare);
    id=ID_ITEM_DIFENSIVO_ARMOR;
    difesa_fisica_iniziale=Math::randomStep(10, 20, 5);
    difesa_magica_iniziale=Math::randomStep(10, 20, 5);
    strcpy (description, armor_description);
    strcpy (name, armor_name);
    apply_rarity();
}


char armor::get_type(){
    return ('a');
}