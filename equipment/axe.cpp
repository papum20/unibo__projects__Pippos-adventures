#ifndef AXE_HPP
#define AXE_HPP
#include <cstring> 

// weapon (int danno fisico, danno magico, velocità d'attacco, )

class Ascia: public Weapon{
    protected:

    public:
        Ascia (int d_f, int d_m, float v_a, char rar[]):Weapon (d_f, d_m, v_a){
            if (strcmp(rar, "raro")==0){
                danno_fisico=danno_fisico+5;
            }
            if (strcmp (rar, "epico")==0){
                danno_fisico=danno_fisico+10;
            }
            if (strcmp (rar, "leggendario")==0){
                danno_fisico=danno_fisico+20;
                //funzione che da un potere alle armi
            }
        }


};