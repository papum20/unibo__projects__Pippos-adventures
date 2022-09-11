#include "physical.hpp"
#include "map_handler.hpp"


Physical::Physical() {
    id = ID_DEFAULT;
    drawn = false;
    updated = false;

    //inizializza animation
    for(int i = 0; i < MAX_ANIMATIONS; i++) 
        animations[i] = NULL;
    animations_n = 0;
	current_animation=0;

    speed = COORDINATE_ONE;
    lastMove = COORDINATE_ZERO;

    animation_rate= FRAMES_PER_SECOND/ANIMATIONS_PER_SECOND;
    animation_counter=animation_rate;
}

void Physical::copyPhysical(Physical B) {
    pos = B.pos;
    size = B.size;
    speed = B.speed;
    id = B.id;
    animations_n = B.animations_n;
    for(int i = 0; i < animations_n; i++) {
        animations[i] = new Animation();
        animations[i]->copy(B.animations[i]);
    }
    current_animation = B.current_animation;
}

void Physical::update(pMap map) {
    updated = true;
}

void Physical::destroy(pMap map) {
    destroyInstance(map);
    delete this;
}
void Physical::destroyInstance(pMap map) {
    // ELIMINA PUNTATORI ANIMAZIONI
    for(int i = 0; i < animations_n; i++) animations[i]->delete_list();
    // ELIMINA OGGETTO
    if(map != NULL) MapHandler::remove(map, this);
}


void Physical::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
    drawn = true;
}
void Physical::drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size) {
    drawAtPosition(scr, win_start, win_size, pos.integer());
}

void Physical::next_animation(){
    /*if (animation_counter>=animation_rate){
        animations[current_animation] = animations[current_animation]->next;
        animation_counter=0;
    }
    else
        animation_counter++;
    */
   animations[current_animation] = animations[current_animation]->next;
}


#pragma region BOOL_GET_SET
    bool Physical::isInanimate() {
        return id >= ID_INANIMATE_S && id <= ID_INANIMATE_E;
    }
    bool Physical::isFixed() {
        return id >= ID_FIXED_S && id <= ID_FIXED_E;
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
    bool Physical::isWeapon() {
        return id >= ID_WEAPON_S && id <= ID_WEAPON_E;
    }
    bool Physical::isItemDifensivo() {
        return id >= ID_ITEM_DIFENSIVO_S && id <= ID_ITEM_DIFENSIVO_E;
    }
    bool Physical::isArtifact() {
        return id >= ID_ARTIFACT_S && id <= ID_ARTIFACT_E;
    }
    bool Physical::findInArray(pPhysical A[ROOM_AREA], int len) {
        bool found = false;
        int i = 0;
        while(!found && i < len) {
            if(A[i] == this) found = true;
            else i++;
        }
        return found;
    }
    bool Physical::animationMask(Coordinate pos) {
	    return getCurrentAnimation().at(pos) != CHAR_EMPTY;
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
    Coordinate Physical::getSpeed() {
        return speed;
    }
    Animation Physical::getCurrentAnimation() {
        return *animations[current_animation];
    }
    Coordinate Physical::lastFrameMovement() {
        return lastMove;
    }

    void Physical::setPosition(Coordinate pos) {
	this->pos = pos;
    } 
    void Physical::resetUpdate() {
        updated = false;
        drawn = false;
    }

    void Physical::resetAnimation(){
        animation_counter=animation_rate;
    }
#pragma endregion BOOL_GET_SET
