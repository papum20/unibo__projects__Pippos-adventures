#include <cstring> 
#include "boots.hpp"

boots::boots():item_difensivo(){
    strcpy(rarity, epic);
    id=ID_ITEM_DIFENSIVO_BOOTS;
    difesa_fisica_iniziale=Math::randomStep(5, 10, 5);
    difesa_magica_iniziale=0; 
    strcpy (description, boots_description); 
    strcpy (name, boots_name);
    apply_rarity();
}

char boots::get_type(){
    return ('b');
}