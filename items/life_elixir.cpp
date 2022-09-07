#include "life_elixir.hpp"

Life_elixir::Life_elixir() : Artifact() {
    life_added=life_increase;
    strcpy (description, elixir_description);
    strcpy (name, elixir_name);
}

void Life_elixir::use_item (pItem item, int &stat){
    stat=stat+life_added;
}