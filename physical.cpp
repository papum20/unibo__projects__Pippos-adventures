#include "physical.hpp"




Physical::Physical() {
        id = ID_DEFAULT;

        //inizializza animation
        for(int i = 0; i < MAX_ANIMATIONS; i++) 
            animations[i] = NULL;
    }

void Physical::destroy() {
    // ELIMINA PUNTATORI ANIMAZIONI
    for(int i = 0; i < MAX_ANIMATIONS; i++)
        if(animations[i] != NULL) animations[i]->delete_list();
    // ELIMINA OGGETTO
    delete this;
}

void Physical::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {

}
void Physical::drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size) {
    drawAtPosition(scr, win_start, win_size, pos);
}

void Physical::next_animation(){
    animations[current_animation]=animations[current_animation]->next;
}


void Physical::moveUp(pMap map){
    Coordinate newpos=pos;
	newpos.y--;
	MapHandler::move(map, this, newpos);
}

void Physical::moveDown(pMap map){
	Coordinate newpos=pos;
	newpos.y++;
	map->move ( this, newpos);
}

void Physical::moveLeft(pMap map){
	Coordinate newpos=pos;
	newpos.x--;
	map->move ( this, newpos);
}

void Physical::moveRight(pMap map){
	Coordinate newpos=pos;
	newpos.x++;
	map->move ( this, newpos);
}

#pragma region BOOL_GET_SET
    bool Physical::isInanimate() {
        return id >= ID_INANIMATE_S && id <= ID_INANIMATE_E;
    }
    bool Physical::isCharacter() {
        return id == ID_PLAYER || (id >= ID_ENEMY_S && id <= ID_ENEMY_E);
    }
    bool Physical::isProjectile() {
        return id >= ID_PROJECTILE_S && id <= ID_PROJECTILE_E;
    }
    /*bool Physical::isItem() {
        return id >= ID_ITEM_S && id <= ID_ITEM_E;
    }*/
    bool Physical::findInArray(pPhysical A[ROOM_AREA], int len) {
        bool found = false;
        int i = 0;
        while(!found && i < len) {
            if(A[i] == this) found = true;
            else i++;
        }
        return found;
    }
    
    int Physical::getId() {
        return id;
    }
    Coordinate Physical::getPosition() {
        return pos;
    }
    Coordinate Physical::getSize() {
        return size;
    }

    void Physical::setPosition(Coordinate pos) {
	this->pos = pos;
}
#pragma endregion BOOL_GET_SET
