#include "chest.hpp"

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