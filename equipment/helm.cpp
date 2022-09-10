#include "helm.hpp"

helm::helm():item_difensivo(){
    //strcpy(rarity, rare);
    id=ID_ITEM_DIFENSIVO_HELM;
    difesa_fisica_iniziale=Math::randomStep(5, 10, 5);
    difesa_magica_iniziale=0;
    strcpy (description, helm_description);
    strcpy (name, helm_name);
    apply_rarity();
}

char helm::get_type(){
    return ('h');
}