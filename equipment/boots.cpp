#include <cstring> 
#include "boots.hpp"

Stivali::Stivali (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag){
            if (strcmp(rar, "raro")==0){
                difesa=difesa+5;
            }
            if (strcmp (rar, "epico")==0){
                difesa=difesa+10;
            }
            if (strcmp (rar, "leggendario")==0){
                difesa=difesa+15;
                //funzione che da un potere oggetti difensivi
            }
}