#include "chest.hpp"

Chest::Chest(){
    
}

Chest::Chest(pWeapon w){
    arma=w;
    type='w';
}

Chest::Chest(pArtifact a){
    artefatto=a;
    type='a';
}

Chest::Chest(pItem_def d){
    item_def=d;
    type='d';
}

pWeapon Chest::open_w(){
    return this->arma;
}

pArtifact Chest::open_a(){
    return this->artefatto;
}

pItem_def Chest::open_d(){
    return this->item_def;
}