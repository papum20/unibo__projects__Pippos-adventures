#ifndef CHEST_HPP
#define CHEST_HPP

#include "weapon.hpp"
#include "artifact.hpp"
#include "item_difensivi.hpp"
#include "inanimate.hpp"
#include "items/key.hpp"

const int chest_width=5;
const int chest_height=3;
const int chest_depth=2;

const int chest_idle_index = 0;

const int chest_idle_states = 1;

const char chest_idle [ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{ {' ', '_', '_', '_', ' '},
  {'|', '-', 'o', '-', '|'},
  {' ', '*', '*', '*', ' '}
};

class Chest: public Inanimate{
    private:
        int idle_index;
    public:
        pWeapon arma;
        pArtifact artefatto;
        pItem_def item_def;
        pKey key;
        char type;
        Chest();
        Chest(pWeapon w);
        Chest (pArtifact a);
        Chest (pItem_def d);
        Chest (pKey k);
        void destroyInstance(pMap map);
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);

        pWeapon open_w();
        pArtifact open_a();
        pItem_def open_d();
};

typedef Chest* pChest;

#endif