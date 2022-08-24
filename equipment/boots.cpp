#include <cstring> 
#include "boots.hpp"

boots::boots (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivi (dif, d_mag, rar, n, desc){
    item_difensivi::apply_rarity();
}

char boots::get_type(){
    return ('b');
}