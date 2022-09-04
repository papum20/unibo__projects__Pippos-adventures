#include "item_difensivi.hpp"

item_difensivo::item_difensivo():item(){
    id=ID_ITEM_DIFENSIVO_S;
    is_equipped=false;
    apply_rarity();
}
item_difensivo::item_difensivo(int dif_f, int dif_m, const char rar[], const char n[], const char desc[]):item() {
    
}


void item_difensivo::copyItemDifensivo(item_difensivo B) {
    difesa_fisica_iniziale=B.difesa_fisica_iniziale;
    difesa_fisica=B.difesa_fisica;
    difesa_magica_iniziale=B.difesa_magica_iniziale;
    difesa_magica=B.difesa_magica;
    is_equipped=B.is_equipped;
    copyItem(B);
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