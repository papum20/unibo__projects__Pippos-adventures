#ifndef CHEST_HPP
#define CHEST_HPP

#include "weapon.hpp"
#include "artifact.hpp"
#include "item_difensivi.hpp"
#include "inanimate.hpp"

const int chest_width=3;
const int chest_height=5;

const char chest [chest_width][chest_height]=
{ {' ', '_', '_', '_', ' '},
  {'|', '-', 'o', '-', '|'},
  {' ', '*', '*', '*', ' '}
};

class Chest: public Inanimate{
    protected:
    public:
        pWeapon arma;
        pArtifact artefatto;
        pItem_def item_def;
        char type;
        Chest();
        Chest(pWeapon w);
        Chest (pArtifact a);
        Chest (pItem_def d);

        pWeapon open_w();
        pArtifact open_a();
        pItem_def open_d();
};

typedef Chest* pChest;

#endif