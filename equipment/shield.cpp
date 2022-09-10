#include "shield.hpp"
#include <cstring> 

shield::shield():item_difensivo(){
    //strcpy(rarity, rare);
    id=ID_ITEM_DIFENSIVO_SHIELD;
    difesa_fisica_iniziale=Math::randomStep(10, 20, 5);
    difesa_magica_iniziale=Math::randomStep(10, 20, 5);
    strcpy (description, shield_description);
    strcpy (name, shield_name);
    apply_rarity();
}

char shield::get_type(){
    return ('s');
}