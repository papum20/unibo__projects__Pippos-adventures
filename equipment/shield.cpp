#include "shield.hpp"
#include <cstring> 

Scudo::Scudo (int dif, int d_mag, char rar[], Character own):item_difensivi (dif, d_mag, own){
            if (strcmp(rar, "raro")==0){
                difesa=difesa+5;
            }
            if (strcmp (rar, "epico")==0){
                difesa=difesa+5;
                difesa_magica=difesa_magica+5;
            }
            if (strcmp (rar, "leggendario")==0){
                difesa=difesa+10;
                difesa_magica=difesa_magica+5;
                //funzione che da un potere oggetti difensivi
            }
}
