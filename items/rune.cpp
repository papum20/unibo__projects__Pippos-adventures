#include "rune.hpp"

Rune::Rune() : Artifact() {
    //strcpy(rarity, epic);
    id=ID_RUNE;
    strcpy (description, rune_description);
    strcpy (name, rune_name);
}
void Rune::use_rune(pItem item){
    item->apply_rune();
}

void Rune::use_item (pItem item, int &stat){
    use_rune(item);
}