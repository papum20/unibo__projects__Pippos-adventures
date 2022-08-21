#include "item.hpp"

item::item (){
    
}

item::item(char rar[]){
    rune_applied=false;
    strcpy (rarity, rar);
}

bool item::check_rarity(){
    if (!rune_applied && strcmp (rarity, legendary)!=0){
        if (strcmp(rarity, common)==0){
            strcpy (rarity, rare);
        }
        if (strcmp(rarity, rare)==0){
            strcpy (rarity, epic);
        }
        if (strcmp(rarity, epic)==0){
            strcpy (rarity, legendary);
        }
        return true;
    }
    else
        return false;
}