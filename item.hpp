#ifndef ITEM_HPP
#define ITEM_HPP

#include "physical.hpp"
#include <cstring>

const int description_length=50;
const int name_length=20;

const char common[]="Common";  
const char rare[]="Rare";
const char epic[]="Epic";
const char legendary[]="Legendary";

class item: public Physical{
    protected:
        bool rune_applied;
        char rarity[15];
        char description[description_length];

        //variabili di movimento
        int move_up_index;
		int move_down_index;
		int move_left_index;
		int move_right_index;
		
		int attack_up_index;
		int attack_down_index;
		int attack_left_index;
		int attack_right_index;
    public:
        item ();
        item(const char rar[], const char desc[]);

        bool check_rarity();

};

typedef item* pItem;

#endif