#ifndef LIFE_ELIXR_HPP
#define LIFE_ELIXIR_HPP

#include "../artifact.hpp"

const int life_increase=1;

const char elixir_description[description_length]="Elisir che aumenta di uno il numero delle vite";
const char elixir_name[name_length]="Elisir della vita";

class Life_elixir:public Artifact {
    protected:
        int life_added;                     //numero di vite che si aggiungono al player
    public:
        Life_elixir();
        Life_elixir(const char n[], const char desc[]);
        
        void use_item (pItem intem, int &stat);         //metodo che aggiunge una vita al player
};

typedef Life_elixir* pElixir;

#endif