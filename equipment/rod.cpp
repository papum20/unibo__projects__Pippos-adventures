#ifndef ROD_HPP
#define ROD_HPP
#include <cstring> 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class Bastone_magico: public Weapon{
    protected:

    public:
        Bastone_Magico (int d_f, int d_m, float v_a, char rar[]):Weapon (d_f, d_m, v_a){
            if (strcmp(rar, "raro")==0){
                danno_magico=danno_magico+5;
            }
            if (strcmp (rar, "epico")==0){
                danno_magico=danno_magico+10;
            }
            if (strcmp (rar, "leggendario")==0){
                danno_magico=danno_magico+15;
                //funzione che da un potere alle armi
            }
        }
};