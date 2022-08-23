#include "rune.hpp"

Rune::Rune():Artifact(){

}

void Rune::use_rune(Weapon w){
    w.apply_rune();
}

void Rune::use_rune (Item_difensivo i_d){
    i_d.apply_rune();
}

void Rune::use_item (pPlayer p){
    
}