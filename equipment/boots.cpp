#include <cstring> 
#include "boots.hpp"

boots::boots():item_difensivo(){
    difesa_fisica_iniziale=0;Math::randomStep(2, 6, 2);
    difesa_magica_iniziale=0; 
    strcpy (description, boots_description); 
    strcpy (name, boots_name);
    apply_rarity();
}

char boots::get_type(){
    return ('b');
}