#include "main/projectile.hpp"
#include "main/map_handler.hpp"

Projectile::Projectile(){

}

Projectile::Projectile(int fisico, int magico, char dir, int shooter):Animate(){
    danno_fisico=fisico;
    danno_magico=magico;
    direction=dir;
    shooter_id=shooter;
    id=ID_PROJECTILE_S;
    main_color = COLOR_PROJECTILE;
    animations_n=projectile_animations_n;
    speed = SPEED_PROJECTILE;
}

void Projectile::copyProjectile(Projectile B) {
    horizontal_size = B.horizontal_size;
    vertical_size=B.vertical_size;
    danno_fisico = B.danno_fisico;
    danno_magico=B.danno_magico;
    shooter_id=B.shooter_id;
    copyAnimate(B);
}


void Projectile::update(pMap map){
    if (!updated){    
        pAlive defender=NULL;
        pPhysical objects[ROOM_AREA];
        Coordinate start = nextPos(), end = Coordinate(Coordinate(start, size), COORDINATE_NEGATIVE);
        /*switch (direction){                 //guardo se ci sono oggetti in collisione con il proiettile
            case 'u':
                start= Coordinate (pos, Coordinate (0, vertical_size.y));
                end = Coordinate (start, Coordinate (vertical_size.x-1, 0));
                break;
            case 'd':
                start= Coordinate (pos, Coordinate (0, -1));
                end = Coordinate (start, Coordinate (vertical_size.x-1, 0));
                break;
            case 'l':
                start = Coordinate (pos, Coordinate (-1, 0));
                end = Coordinate (start, Coordinate (0, horizontal_size.y-1));
                break;
            case 'r':
                start = Coordinate (pos, Coordinate (horizontal_size.x, 0));
                end = Coordinate (start, Coordinate (0, horizontal_size.y-1));
                break;
        }*/

        int dim=MapHandler::checkRectangle(map, objects, start, end);       //numero di oggetti in collisione
        
        if ((!findInArray(objects, dim) && dim > 0) || dim > 1){    
            for (int i=0; i<dim; i++){
                if (objects[i]->getId()!=this->shooter_id && objects[i]->isCharacter()){         //se si tratta di un personaggio diverso dalla categoria di colui che ha sparato, 
                    defender=MapHandler::checkAlive(map, objects[i]->getPosition());    //mi serve un puntatore a character
                    defender->changeCurrentHealth(calculate_damage(defender));    //cambio la vita in base ai danni subiti
                }
            }
            destroy(map);                                                              //visto che ha colliso, elimino il proiettile
        }
        else{                                               //se non ci sono state collisioni
            move(map);
            //switch (direction){                             //il proiettile si muove verso la sua direzione
            //    case 'u':
            //        moveUp(map);
            //        break;
            //    case 'd':
            //        moveDown(map);
            //        break;
            //    case 'l':
            //        moveLeft(map);
            //        break;
            //    case 'r':
            //        moveRight(map);
            //        break;
            //}
            Physical::update(map);
        }
    }
}



int Projectile::calculate_damage(pAlive c){
    int damage;
    damage=danno_fisico-(c->difesa_fisica/2)+danno_magico-(c->difesa_magica/2);
    if (damage>0)
        return (-(damage));
    else
        return 0;
}

void Projectile::setPosition(Coordinate shooter_pos, Coordinate shooter_size, char shooter_direction){
    direction=shooter_direction;
    switch (direction){
        case 'u':
            size = vertical_size;
            this->pos.x=shooter_pos.x+(shooter_size.x)/2-size.x/2;
            this->pos.y=shooter_pos.y+shooter_size.y;
            current_animation=move_up_index;
            break;
        case 'd':
            size = vertical_size;
            this->pos.x=shooter_pos.x+(shooter_size.x)/2-size.x/2;
            this->pos.y=shooter_pos.y-size.y;
            current_animation=move_down_index;
            break;
        case 'l':
            size = horizontal_size;
            this->pos.x=shooter_pos.x-size.x;
            this->pos.y=shooter_pos.y+(shooter_size.y)/2-size.y/2;
            current_animation=move_left_index;
            break;
        case 'r':
            size = horizontal_size;
            this->pos.x=shooter_pos.x+shooter_size.x;
            this->pos.y=shooter_pos.y+(shooter_size.y)/2-size.y/2;
            current_animation=move_right_index;
            break;
    }
}



void Projectile::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
    if(!drawn) {
		Coordinate win_end = Coordinate(win_start, win_size);
		Coordinate local = Coordinate(COORDINATE_ZERO, ANIMATION_SIZE, COORDINATE_ZERO, getCurrentAnimation().size);	//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(Coordinate(pos, local), win_start, win_end);            //coordinata globale di relative, sulla mappa
			if(global.inOwnBounds() && animationMask(local))            		        	        //se il punto è interno alla finestra da disegnare e deve disegnare qualcosa
				scr[global.rel_int_y()][global.rel_int_x()].edit(getCurrentAnimation().at(local), main_color, -1, CELL_NO_ATTR);
            local.next();
		} while(!local.equals(COORDINATE_ZERO));
		drawn = true;
	}
}


