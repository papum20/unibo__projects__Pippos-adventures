#ifndef ANIMATE_HPP
#define ANIMATE_HPP


#include "main/physical.hpp"


class Animate : public Physical {
	protected:

		attr_t main_color;

		Coordinate toDirection();		//da direzione carattere a direzione coordinat
        Coordinate nextPos();


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

		char direction;							// u sopra, d sotto, l sinistra, r destra
		
		Animate();
		void copyAnimate(Animate B);

		attr_t get_MainColor();
		
		//MOVE
		void move(pMap map);
		void moveUp(pMap map);
		void moveDown(pMap map);
		void moveLeft(pMap map);
		void moveRight(pMap map);
};


#endif