#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "animate.hpp"
#include "alive.hpp"


const int projectile_animations_n = 4;


class Projectile: public Animate{
    protected:
    public:
        Coordinate horizontal_size;
		Coordinate vertical_size;
        int danno_fisico;
        int danno_magico;
        int shooter_id;
        Projectile();
        //Projectile (pWeapon w);
        Projectile (int fisico, int magico, char dir, int shooter);
        void copyProjectile(Projectile B);
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra

        void update (pMap map);
        int calculate_damage(pAlive c);
        void setPosition (Coordinate shooter_pos, Coordinate shooter_size, char shooter_direction);
};

typedef Projectile *pProjectile;


#endif