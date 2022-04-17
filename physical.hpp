#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP


//struttura della lista degli array dell'animazione del players
struct animation_player{
 char player[3][3];
 animation_player *next;
 };
typedef animation_player *p_animation_player;

class Physical {
	protected:
		int xPos;
		int yPos;
	public:
		Physical();
};

typedef Physical *pPhysical;




#endif PHYSICAL_HPP