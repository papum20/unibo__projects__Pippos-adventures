#ifndef LIFE_ELIXR_HPP
#define LIFE_ELIXIR_HPP

#include "../artifact.hpp"

const int life_increase=1;

class Life_elixir:public Artifact {
    protected:
        int life_added;                     //numero di vite che si aggiungono al player
    public:
        Life_elixir();
        Life_elixir(const char n[], const char desc[]);
        
        void use_item (pPlayer p);         //metodo che aggiunge una vita al player
};

typedef Life_elixir* pElixir;

#endif