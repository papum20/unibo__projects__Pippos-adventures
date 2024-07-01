#include "items/life_elixir.hpp"

Life_elixir::Life_elixir() : Artifact() {
    //strcpy(rarity, rare);
    id=ID_LIFE_ELIXIR;
    //life_added=life_increase;
    increment=life_increase;
    max_stat=p_max_lives;
    strcpy (description, elixir_description);
    strcpy (name, elixir_name);
    strcpy(text_error, life_full);
    strcpy(text_success, gain_heart);
}

