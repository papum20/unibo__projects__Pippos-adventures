#include "physical.hpp"




Physical::Physical() {
        id = ID_DEFAULT;

        //inizializza animation
        for(int i = 0; i < MAX_ANIMATIONS; i++) 
            animations[i] = NULL;
    }

void Physical::destroy() {
    // ELIMINA PUNTATORI ANIMAZIONI

    // ELIMINA OGGETTO
    delete this;
}

void Physical::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos) {

}
void Physical::drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start) {
    drawAtPosition(scr, win_start, pos);
}

void Physical::next_animation(){
    animations[current_animation]=animations[current_animation]->next;
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
    /*bool Physical::isPlaceholder() {
        return id == ID_PLACEHOLDER;
    }*/

/*    pPhysical Physical::checkPosition(pPhysical map[], Coordinate pos) {
		if(pos.inBounds(Coordinate(0, 0), size) && map[pos.single()]->getId() != ID_FLOOR)
			return map[pos.single()];
		else return NULL;
	}
    pPhysical Physical::checkLine(pPhysical map[], Coordinate start, Coordinate end) {
        Coordinate delta = Coordinate(end, start.getNegative());
        int deltaMax = delta.x;
        if(delta.y > delta.x) deltaMax = delta.y;
        delta.times(1. / deltaMax, 1. / deltaMax);

        Coordinate i = start;
        pPhysical target = NULL;
        while(!i.equals(end) && target == NULL) {
            target = checkPosition(map, i);
            i = Coordinate(i, delta);
        }
        if(target == NULL) return checkPosition(map, end);
        else return NULL;
    }*/

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
