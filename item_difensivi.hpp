#ifndef ITEM_DIFENSIVI_HPP
#define ITEM_DIFENSIVI_HPP

#include "item.hpp"


class item_difensivo: public item{
    protected:
    public:
        int difesa_fisica_iniziale;
        int difesa_fisica;
        int difesa_magica_iniziale;
        int difesa_magica;
        bool is_equipped;
        item_difensivo();
        item_difensivo(int dif_f, int dif_m, const char rar[], const char n[], const char desc[]);
		void copy(item_difensivo B);			//copia i parametri di B

        void apply_rune();
        void apply_rarity();
        virtual char get_type();
};

typedef item_difensivo* pItem_def;

#endif