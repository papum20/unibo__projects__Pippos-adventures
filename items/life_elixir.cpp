#include "life_elixir.hpp"

Life_elixir::Life_elixir():Artifact(){
    life_added=life_increase;
}

void Life_elixir::use_item (pPlayer p){
    p->modify_lifes(life_added);
}