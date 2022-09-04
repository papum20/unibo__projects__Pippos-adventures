#ifndef ITEM_HPP
#define ITEM_HPP

#include "animate.hpp"
#include <cstring>
#include "math.hpp"

const int description_length=200;
const int name_length=20;
const int rarity_length=10;

const char common[rarity_length]="Common";  
const char rare[rarity_length]="Rare";
const char epic[rarity_length]="Epic";
const char legendary[rarity_length]="Legendary";

class item: public Animate{
    public:
        char rarity[15];
        char description[description_length];
        char name[20];
        char type[20];
        
        item ();
        item (const char n[], const char desc[]);
        item(const char rar[], const char n[], const char desc[]);
        void copyItem(item B);

        bool check_rarity();

};

typedef item* pItem;

#endif