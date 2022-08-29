#include "item.hpp"

item::item():Physical(){
    
}

item::item(const char n[], const char desc[]){
    strcpy (name, n);
    strcpy (description, desc);
}

item::item(const char rar[], const char n[], const char desc[]){
    rune_applied=false;
    strcpy (rarity, rar);
    strcpy(description, desc);
    strcpy (name, n);
}

bool item::check_rarity(){
    if (!rune_applied && strcmp (rarity, legendary)!=0){
        if (strcmp(rarity, common)==0){
            strcpy (rarity, rare);
        }
        else if (strcmp(rarity, rare)==0){
            strcpy (rarity, epic);
        }
        else if (strcmp(rarity, epic)==0){
            strcpy (rarity, legendary);
        }
        return true;
    }
    else
        return false;
}