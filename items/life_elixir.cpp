#include "life_elixir.hpp"

Life_elixir::Life_elixir(const char n[], const char desc[]):Artifact(n, desc){
    life_added=life_increase;
}

void Life_elixir::use_item (pItem item, int &stat){
    //p->modify_lifes(life_added);
}