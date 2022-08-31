#ifndef WEAPON_HPP
#define WEAPON_HPP

using namespace std;

#include "coordinate.hpp"
#include "item.hpp"
//#include "character.hpp"
#include "projectile.hpp"


const int WEAPON_ANIMATION_WIDTH = 10;
const int WEAPON_ANIMATION_HEIGHT = 10;

class Weapon : public item {
	private:

	public:
		int danno_fisico_iniziale;
		int danno_magico_iniziale;
		int danno_fisico;
		int danno_magico;
	public:
		bool is_melee;
		bool is_equipped;
		Weapon();
		Weapon(int danno_f, int danno_m, const char rar[], const char n[], const char desc[]);
		void copy(Weapon B);		//copia gli attributi di B

		void apply_rune();
		void apply_rarity();
};

typedef Weapon* pWeapon;


#endif