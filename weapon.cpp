#include "weapon.hpp"

Weapon::Weapon ():item(){
    apply_rarity();
    is_equipped=false;
    id=WEAPON_ID;
}


void Weapon::apply_rune(){
    if (this->check_rarity())
        apply_rarity();
}

void Weapon::apply_rarity (){
    if (strcmp(rarity, rare)==0){
        danno_fisico=danno_fisico_iniziale*2;
        danno_magico=danno_magico_iniziale*2;
        }
    if (strcmp (rarity, epic)==0){
        danno_fisico=danno_fisico_iniziale*3;
        danno_magico=danno_magico_iniziale*3;
    }
    if (strcmp (rarity, legendary)==0){
        danno_fisico=danno_fisico_iniziale*4;
        danno_magico=danno_magico_iniziale*4;
    }
}
