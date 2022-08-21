#ifndef ITEM_HPP
#define ITEM_HPP


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
    public:
        item ();
        item(char rar[]);

        bool check_rarity();

};

typedef item* pItem;

#endif