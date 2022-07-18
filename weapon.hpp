#ifndef WEAPON_HPP
#define WEAPON_HPP



#include "item.hpp"


class Weapon : public Item {
	private:

	protected:
		int base_dmg;
		float attack_speed;							//ogni quanto un'arma attacca
	public:
		Weapon(int base_dmg, float attack_speed);
};




#endif