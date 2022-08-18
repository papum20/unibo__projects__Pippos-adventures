#include "necklace.hpp"
#include <cstring>

necklace::necklace (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag, rar){
    item_difensivi::apply_rarity();
}

char necklace::get_type(){
    return ('n');
}