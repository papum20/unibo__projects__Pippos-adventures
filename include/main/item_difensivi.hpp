#ifndef ITEM_DIFENSIVI_HPP
#define ITEM_DIFENSIVI_HPP

#include "main/item.hpp"


class item_difensivo: public item{
    protected:
    public:
        int difesa_fisica_iniziale;
        int difesa_fisica;
        int difesa_magica_iniziale;
        int difesa_magica;
        bool is_equipped;
        item_difensivo();
		void copyItemDifensivo(item_difensivo B);			//copia i parametri di B

        void apply_rune();
        void apply_rarity();
        virtual char get_type();
};

typedef item_difensivo* pItem_def;

#endif