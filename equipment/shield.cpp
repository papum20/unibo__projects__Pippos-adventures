#ifndef SHIELD_HPP
#define SHIELD_HPP
#include <cstring> 

class Scudo: public item_difensivi{
    protected:

    public:
        Scudo (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag){
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

};