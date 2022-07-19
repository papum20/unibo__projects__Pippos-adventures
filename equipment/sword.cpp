#include "sword.hpp"
#include <cstring> 

Spada::Spada (int d_f, int d_m, float v_a, char rar[]):Weapon (d_f, d_m, v_a){
            if (strcmp(rar, "raro")==0){
                danno_fisico=danno_fisico+5;
            }
            if (strcmp (rar, "epico")==0){
                danno_fisico=danno_fisico+5;
                danno_magico=danno_magico+5;
            }
            if (strcmp (rar, "leggendario")==0){
                danno_fisico=danno_fisico+10;
                danno_magico=danno_magico+10;
                //funzione che da un potere alle armi
            }
}
