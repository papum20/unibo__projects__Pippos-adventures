#include "shield.hpp"
#include <cstring> 

shield::shield():item_difensivo(){

}

shield::shield (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivo (dif, d_mag, rar, n, desc){
    apply_rarity();
}

char shield::get_type(){
    return ('s');
}