#include "projectile.hpp"
#include "map_handler.hpp"

Projectile::Projectile(){

}

/*Projectile::Projectile(pWeapon w):Physical(){
    danno_fisico=w->danno_fisico;
    danno_magico=w->danno_magico;
    direction=w->direction;
    shooter_id=w->owner_id;
    id=ID_PROJECTILE_S;
}*/
Projectile::Projectile(int fisico, int magico, char dir, int shooter):Animate(){
    danno_fisico=fisico;
    danno_magico=magico;
    direction=dir;
    shooter_id=shooter;
    id=ID_PROJECTILE_S;
}


void Projectile::update(pMap map){
    pAlive defender=NULL;
    pPhysical objects[ROOM_AREA];
    Coordinate end;
    switch (direction){                 //guardo se ci sono oggetti in collisione con il proiettile
        case 'u':
            end=Coordinate (Coordinate (pos, vertical_size), Coordinate (-1, -1));
            break;
        case 'd':
            end=Coordinate (Coordinate (pos, vertical_size), Coordinate (-1, -1));
            break;
        case 'l':
            end=Coordinate (Coordinate (pos, horizontal_size), Coordinate (-1, -1));
            break;
        case 'r':
            end= Coordinate (Coordinate (pos, horizontal_size), Coordinate (-1, -1));
            break;
    }

    int dim=MapHandler::checkRectangle(map, objects, this->pos, end);       //numero di oggetti in collisione
    
    if (dim!=0){                                                            //se è maggiore di zero, calcolo le collisioni
        for (int i=0; i<dim; i++){
            if (objects[i]->getId()!=this->shooter_id && objects[i]->isCharacter()){         //se si tratta di un personaggio diverso dalla categoria di colui che ha sparato, 
                defender=MapHandler::checkAlive(map, objects[i]->getPosition());    //mi serve un puntatore a character
                defender->changeCurrentHealth(calculate_damage(defender));    //cambio la vita in base ai danni subiti
            }
        }
        destroy();                                                              //visto che ha colliso, elimino il proiettile
    }
    else{                                               //se non ci sono state collisioni
        switch (direction){                             //il proiettile si muove verso la sua direzione
            case 'u':
                moveUp(map);
                break;
            case 'd':
                moveDown(map);
                break;
            case 'l':
                moveLeft(map);
                break;
            case 'r':
                moveRight(map);
                break;
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

void Projectile::setPosition(Coordinate shooter_pos, Coordinate shooter_size){
    switch (direction){
        case 'u':
            this->pos.x=shooter_pos.x+(shooter_size.x)/2-size.x/2;
            this->pos.y=shooter_pos.y+shooter_size.y;
            break;
        case 'd':
            this->pos.x=shooter_pos.x+(shooter_size.x)/2-size.x/2;
            this->pos.y=shooter_pos.y-size.y;
            break;
        case 'l':
            this->pos.x=shooter_pos.x-size.x;
            this->pos.y=shooter_pos.y+(shooter_size.y)/2-size.y/2;
            break;
        case 'r':
            this->pos.x=shooter_pos.x+shooter_size.x;
            this->pos.y=shooter_pos.y+(shooter_size.y)/2-size.y/2;
            break;
    }
}