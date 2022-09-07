#include "item.hpp"

item::item():Animate(){
    strcpy(rarity, common);
}

void item::copyItem(item B) {
    strcpy(rarity, B.rarity);
    strcpy(description, B.description);
    strcpy(name, B.name);
    copyAnimate(B);
}

void apply_rune(){

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