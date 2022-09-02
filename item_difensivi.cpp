#include "item_difensivi.hpp"

item_difensivo::item_difensivo():item(){
    id=DEFENSIVE_ITEM_ID;
    is_equipped=false;
    apply_rarity();
}

void item_difensivo::apply_rune(){
    if (this->check_rarity())
        apply_rarity();
}

void item_difensivo::apply_rarity(){
    if (strcmp(rarity, rare)==0){
        difesa_fisica=difesa_fisica_iniziale*2;
        difesa_magica=difesa_magica_iniziale*2;
        }
    if (strcmp (rarity, epic)==0){
        difesa_fisica=difesa_fisica_iniziale*3;
        difesa_magica=difesa_magica_iniziale*3;
    }
    if (strcmp (rarity, legendary)==0){
        difesa_fisica=difesa_fisica_iniziale*4;
        difesa_magica=difesa_magica_iniziale*4;
    }
}