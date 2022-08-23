#include "necklace.hpp"
#include <cstring>

necklace::necklace (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivi (dif, d_mag, rar, n, desc){
    item_difensivo::apply_rarity();
}

char necklace::get_type(){
    return ('n');
}