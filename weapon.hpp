#ifndef WEAPON_HPP
#define WEAPON_HPP

using namespace std;

#include "coordinate.hpp"
#include "item.hpp"
#include "projectile.hpp"

const int player_x_coordinate = 3;
const int player_y_coordinate = 2;


class Weapon : public item {
	protected:
		Coordinate offset;	//punto in cui "attaccare" l'animazione del character su quella della weapon, rispetto all'angolo in basso a sinistra
		
	public:
		Projectile projectile;
		Coordinate horizontal_size;
		Coordinate vertical_size;
		int delta_x_horizontal;
		int delta_y_vertical;
		int danno_fisico_iniziale;
		int danno_magico_iniziale;
		int danno_fisico;
		int danno_magico;
		bool is_melee;
		bool is_equipped;
		int owner_id;

		int vertical_attack_states;
		int horizontal_attack_states;
		int vertical_attack_animation;
		int horizontal_attack_animation;

		Weapon();
		Weapon(int danno_f, int danno_m, const char rar[], const char n[], const char desc[]);
		void copyWeapon(Weapon B);		//copia gli attributi di B

		void apply_rune();
		void apply_rarity();
		 pProjectile shoot();

		Coordinate getOffset();
		void initiate_attack(char d);
		bool check_frame();

		bool animationMask(Coordinate pos);		//true se la posizione, relativa all'animazione dell'arma, copre il personaggio o quello che c'è sotto
};

typedef Weapon* pWeapon;




#endif