#include "shield.hpp"
#include <cstring> 

shield::shield():item_difensivo(){
    difesa_fisica_iniziale=Math::randomStep(10, 20, 5);
    difesa_magica_iniziale=Math::randomStep(10, 20, 5);
    strcpy (description, shield_description);
    apply_rarity();
}

char shield::get_type(){
    return ('s');
}