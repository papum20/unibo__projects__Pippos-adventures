#ifndef ITEM_HPP
#define ITEM_HPP

#include "animate.hpp"
#include <cstring>
#include "math.hpp"

const int description_length=200;
const int name_length=25;
const int rarity_length=12;

const char common[rarity_length]="comune";  
const char rare[rarity_length]="raro";
const char epic[rarity_length]="epico";
const char legendary[rarity_length]="leggendario";

class item: public Animate{
    public:
        char rarity[rarity_length];
        char description[description_length];
        char name[name_length];
        
        item ();
        void copyItem(item B);
        virtual void apply_rune();
        bool check_rarity();

};

typedef item* pItem;

#endif