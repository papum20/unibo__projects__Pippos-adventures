#ifndef ITEM_HPP
#define ITEM_HPP

#include "physical.hpp"
#include <cstring>
#include "math.hpp"

const int description_length=200;
const int name_length=20;

const char common[]="Common";  
const char rare[]="Rare";
const char epic[]="Epic";
const char legendary[]="Legendary";

class item: public Physical{
    public:
        char rarity[15];
        char description[description_length];
        char name[20];
        char type[20];
        
        item ();
        item (const char n[], const char desc[]);
        item(const char rar[], const char n[], const char desc[]);

        bool check_rarity();

};

typedef item* pItem;

#endif