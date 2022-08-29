#include "weapon.hpp"

Weapon::Weapon (int danno_f, int danno_m, const char rar[], const char n[], const char desc[]):item(rar, n, desc){
    danno_fisico=danno_f;
    danno_magico=danno_m;
    
    if (strcmp(rar, common)==0){
        danno_fisico_iniziale=danno_fisico;
        danno_magico_iniziale=danno_magico;
    }
    if (strcmp(rar, rare)==0){
        danno_fisico_iniziale=danno_fisico/2;
        danno_magico_iniziale=danno_magico/2;
    }
    if (strcmp(rar, epic)==0){
        danno_fisico_iniziale=danno_fisico/3;
        danno_magico_iniziale=danno_magico/3;
    }
    if (strcmp(rar, legendary)==0){
        danno_fisico_iniziale=danno_fisico/4;
        danno_magico_iniziale=danno_magico/4;
    }

    is_equipped=false;
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