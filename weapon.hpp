#ifndef WEAPON_HPP
#define WEAPON_HPP


#include "coordinate.hpp"
#include "item.hpp"
#include "character.hpp"

const int ANIMATION_WIDTH = 10;
const int ANIMATION_HEIGHT = 10;

class Weapon : public Item {
	private:

	protected:
		int danno_fisico;
		int danno_magico;
		float velocita_a;							//ogni quanto un'arma attacca
		Coordinate pos;
		Character owner;
	public:
		Weapon(int danno_f, int danno_m, float velcoita_a, Character own);
};




#endif