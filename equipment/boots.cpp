#include <cstring> 
#include "boots.hpp"

boots::boots (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivo(dif, d_mag, rar, n, desc){
    apply_rarity();
}

char boots::get_type(){
    return ('b');
}