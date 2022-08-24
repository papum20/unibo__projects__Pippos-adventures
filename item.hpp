#ifndef ITEM_HPP
#define ITEM_HPP

const int description_length=50;
const int name_length=20;
const int chest_width=3;
const int chest_height=5;

const char chest [chest_width][chest_height]=
{ {' ', '_', '_', '_', ' '},
  {'|', '-', 'o', '-', '|'},
  {' ', '*', '*', '*', ' '}
};

const char common[]="Common";  
const char rare[]="Rare";
const char epic[]="Epic";
const char legendary[]="Legendary";

class item: public Physical{
    protected:
        bool rune_applied;
        char rarity[15];
        char description[description_length];
    public:
        item ();
        item(const char rar[], const char desc[]);

        bool check_rarity();

};

typedef item* pItem;

#endif