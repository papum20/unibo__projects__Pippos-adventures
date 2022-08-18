#include <cstring> 
#include "boots.hpp"

boots::boots (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag, rar){
    item_difensivi::apply_rarity();
}

char boots::get_type(){
    return ('b');
}