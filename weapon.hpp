#ifndef WEAPON_HPP
#define WEAPON_HPP

using namespace std;

#include "coordinate.hpp"
#include "item.hpp"
//#include "character.hpp"


const int WEAPON_ANIMATION_WIDTH = 10;
const int WEAPON_ANIMATION_HEIGHT = 10;

class Weapon : public item {
	private:

	public:
		int danno_fisico_iniziale;
		int danno_magico_iniziale;
		int danno_fisico;
		int danno_magico;
		bool is_equipped;
		char name[name_length];
		bool is_melee;
	public:
		Weapon(int danno_f, int danno_m, const char rar[], const char n[], const char desc[]);

		void apply_rune();
		void apply_rarity();
};

typedef Weapon* pWeapon;


#endif