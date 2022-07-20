#include "axe.hpp"
#include <cstring>

Ascia::Ascia (int d_f, int d_m, float v_a, char rar[], Character own):Weapon (d_f, d_m, v_a, own){
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