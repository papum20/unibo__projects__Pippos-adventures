#include "rod.hpp"
#include <cstring>

Bastone_magico::Bastone_Magico (int d_f, int d_m, float v_a, char rar[], Character own):Weapon (d_f, d_m, v_a, own){
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