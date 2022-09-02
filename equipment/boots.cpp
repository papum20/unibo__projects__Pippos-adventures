#include <cstring> 
#include "boots.hpp"

boots::boots():item_difensivo(){
    difesa_fisica_iniziale=Math::randomStep(5, 10, 5);
    difesa_magica_iniziale=0; 
    strcpy (description, boots_description); 
}

char boots::get_type(){
    return ('b');
}