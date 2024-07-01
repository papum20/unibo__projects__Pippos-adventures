#include "items/rune.hpp"

Rune::Rune() : Artifact() {
    //strcpy(rarity, epic);
    id=ID_RUNE;
    strcpy (description, rune_description);
    strcpy (name, rune_name);
    strcpy(text_success, upgrade_equip);
}
