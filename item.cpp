#include "item.hpp"

item::item():Physical(){
    strcpy(rarity, common);
}

item::item(const char n[], const char desc[]){
    strcpy (name, n);
    strcpy (description, desc);
    strcpy(rarity, common);
}

item::item(const char rar[], const char n[], const char desc[]){
    strcpy (rarity, rar);
    strcpy(description, desc);
    strcpy (name, n);
}

bool item::check_rarity(){
    if (strcmp (rarity, legendary)!=0){
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