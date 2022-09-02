#include "helm.hpp"

helm::helm():item_difensivo(){
    difesa_fisica_iniziale=Math::randomStep(5, 10, 5);
    difesa_magica_iniziale=0;
    strcpy (description, helm_description);
}

char helm::get_type(){
    return ('h');
}