#include "armor.hpp"

armor::armor():item_difensivo(){
    difesa_fisica_iniziale=Math::randomStep(10, 20, 5);
    difesa_magica_iniziale=Math::randomStep(10, 20, 5);
    strcpy (description, armor_description);
}


char armor::get_type(){
    return ('a');
}