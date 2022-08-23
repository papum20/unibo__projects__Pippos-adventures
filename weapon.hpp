#ifndef WEAPON_HPP
#define WEAPON_HPP

using namespace std;

#include "coordinate.hpp"
#include "item.hpp"
#include "character.hpp"

const int ANIMATION_WIDTH = 10;
const int ANIMATION_HEIGHT = 10;

class Weapon : public item {
	private:

	public:
		int danno_fisico_iniziale;
		int danno_magico_iniziale;
		int danno_fisico;
		int danno_magico;
		bool is_equipped;
	public:
		Weapon(int danno_f, int danno_m, const char rar[]);

		void apply_rune();
		void apply_rarity();
};

typedef Weapon* pWeapon;


#endif