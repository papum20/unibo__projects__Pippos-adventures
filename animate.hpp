#ifndef ANIMATE_HPP
#define ANIMATE_HPP


#include "physical.hpp"


class Animate : public Physical {
	protected:
		char direction;							// u sopra, d sotto, l sinistra, r destra

		attr_t main_color;

	public:
		//variabili per array di movimento, si trovano qui perchè servono a weapon, character e projectile
		int idle_index;

		int move_up_index;
		int move_down_index;
		int move_left_index;
		int move_right_index;
		
		int attack_up_index;
		int attack_down_index;
		int attack_left_index;
		int attack_right_index;
		
		Animate();
		virtual void copy(Animate B);

		attr_t get_MainColor();
		
		//MOVE
		void moveUp(pMap map);
		void moveDown(pMap map);
		void moveLeft(pMap map);
		void moveRight(pMap map);
};


#endif