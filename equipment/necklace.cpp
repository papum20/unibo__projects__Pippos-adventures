#include "necklace.hpp"
#include <cstring>

necklace::necklace():item_difensivo(){

}

necklace::necklace (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivo (dif, d_mag, rar, n, desc){
    apply_rarity();
}

char necklace::get_type(){
    return ('n');
}