#include "life_elixir.hpp"

Life_elixir::Life_elixir() : Artifact() {
    //strcpy(rarity, rare);
    id=ID_LIFE_ELIXIR;
    life_added=life_increase;
    strcpy (description, elixir_description);
    strcpy (name, elixir_name);
}

void Life_elixir::use_item (pItem item, int &stat, System_text* text){
    if (stat==5)
        text->insert_string(life_full);  
    else{    
        stat=stat+life_added;
        text->insert_string(gain_heart);
    }
}