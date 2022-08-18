#include "shield.hpp"
#include <cstring> 

shield::shield (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag, rar){
    item_difensivi::apply_rarity();
}

char shield::get_type(){
    return ('s');
}