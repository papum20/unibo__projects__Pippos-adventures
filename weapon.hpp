#ifndef WEAPON_HPP
#define WEAPON_HPP

using namespace std;

#include "coordinate.hpp"
#include "item.hpp"
//#include "character.hpp"
#include "projectile.hpp"


class Weapon : public item {
	private:

	protected:
		Coordinate offset;	//punto in cui "attaccare" l'animazione del character su quella della weapon, rispetto all'angolo in basso a sinistra
		//int delta_x;	//up e down	
		//int delta_y;	//left e right

	public:
		int danno_fisico_iniziale;
		int danno_magico_iniziale;
		int danno_fisico;
		int danno_magico;
		bool is_melee;
		bool is_equipped;

		//coordinate per calcolare collisioni
		
		Weapon();
		Weapon(int danno_f, int danno_m, const char rar[], const char n[], const char desc[]);
		void copy(Weapon B);		//copia gli attributi di B

		void apply_rune();
		void apply_rarity();
		virtual void shoot(){};

		Coordinate getOffset();
};

typedef Weapon* pWeapon;


#endif