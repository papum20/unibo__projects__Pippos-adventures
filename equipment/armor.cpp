#include "armor.hpp"

armor::armor (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivi (dif, d_mag, rar, n, desc){
    item_difensivo::apply_rarity();
}

char armor::get_type(){
    return ('a');
}