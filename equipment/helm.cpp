#include "helm.hpp"

helm::helm():item_difensivo(){

}

helm::helm (int dif, int d_mag, const char rar[], const char n[], const char desc[]):item_difensivo (dif, d_mag, rar, n, desc){
    apply_rarity();
}

char helm::get_type(){
    return ('h');
}