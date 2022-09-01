#include "item_difensivi.hpp"

item_difensivo::item_difensivo():item(){
    id=DEFENSIVE_ITEM_ID;
}

item_difensivo::item_difensivo(int dif_f, int dif_m, const char rar[], const char n[], const char desc[]):item(rar, n, desc){
    difesa_fisica=dif_f;
    difesa_magica=dif_m;
    if (strcmp(rar, common)==0){
        difesa_fisica_iniziale=difesa_fisica;
        difesa_magica_iniziale=difesa_magica;
    }
    if (strcmp(rar, rare)==0){
        difesa_fisica_iniziale=difesa_fisica/2;
        difesa_magica_iniziale=difesa_magica/2;
    }
    if (strcmp(rar, epic)==0){
        difesa_fisica_iniziale=difesa_fisica/3;
        difesa_magica_iniziale=difesa_magica/3;
    }
    if (strcmp(rar, legendary)==0){
        difesa_fisica_iniziale=difesa_fisica/4;
        difesa_magica_iniziale=difesa_magica/4;
    }
    is_equipped=false;
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