#ifndef BOW_HPP
#define BOW_HPP
#include <cstring> 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class Arco: public Weapon{
    protected:

    public:
        Arco (int d_f, int d_m, float v_a, char rar[]):Weapon (d_f, d_m, v_a){
            if (strcmp(rar, "raro")==0){
                danno_fisico=danno_fisico+5;
            }
            if (strcmp (rar, "epico")==0){
                danno_fisico=danno_fisico+5;
                velocita_attacco=velocita_attacco*1.25;
            }
            if (strcmp (rar, "leggendario")==0){
                danno_fisico=danno_fisico+10;
                velocita_attacco=velocita_attacco*1.5;
                //funzione che da un potere alle armi
            }
        }


};