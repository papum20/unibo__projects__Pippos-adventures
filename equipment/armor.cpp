#ifndef ARMOR_HPP
#define ARMOR_HPP
#include <cstring> 

class Armatura: public item_difensivi{
    protected:

    public:
        Armatura (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag){
            if (strcmp(rar, "raro")==0){
                difesa=difesa+5;
            }
            if (strcmp (rar, "epico")==0){
                difesa=difesa+10;
                difesa_magica=difesa_magica+5;
            }
            if (strcmp (rar, "leggendario")==0){
                difesa=difesa+15;
                difesa_magica=difesa_magica+10;
                //funzione che da un potere oggetti difensivi
            }
        }


};