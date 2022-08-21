#include "item_difensivi.hpp"

item_difensivi::item_difensivi(int dif_f, int dif_m, char rar[]):item(rar){
    difesa_fisica_iniziale=dif_f;
    difesa_fisica_iniziale=dif_m;
}

void item_difensivi::apply_rune(){
    if (item::check_rarity)
        apply_rarity();
}

void item_difensivi::apply_rarity(){
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