#include "shield.hpp"
#include <cstring> 

shield::shield (int dif, int d_mag, const char rar[]):item_difensivi (dif, d_mag, rar){
    item_difensivo::apply_rarity();
}

char shield::get_type(){
    return ('s');
}