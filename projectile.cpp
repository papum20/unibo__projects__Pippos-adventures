#include "projectile.hpp"

Projectile::Projectile(){

}

Projectile::Projectile(pWeapon w):Physical(){
    danno_fisico=w->danno_fisico;
    danno_magico=w->danno_magico;
    direction=w->direction;
    shooter_id=w->owner_id;
    id=PROJECTILE_ID;
}


void Projectile::update(pMap map){
    pCharacter defender=NULL;
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
            if (objects[i]->id!=this->shooter_id && objects[i]->isCharacter()){         //se si tratta di un personaggio diverso dalla categoria di colui che ha sparato, 
                defender=MapHandler::checkCharacter(map, objects[i]->getPosition());       //mi serve un puntatore a character
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



int Projectile::calculate_damage(pCharacter c){
    int damage;
    damage=danno_fisico-(c->difesa_fisica/2)+danno_magico-(c->difesa_magica/2);
    if (damage>0)
        return (-(damage));
    else
        return 0;
}