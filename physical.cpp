#include "physical.hpp"




Physical::Physical() {
        id = ID_DEFAULT;

        //inizializza animation
        for(int i = 0; i < MAX_ANIMATION; i++) 
            animation[i] = NULL;
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



#pragma region BOOL_GET_SET
    bool Physical::isInanimate() {
        return id >= ID_INANIMATE_S && id <= ID_INANIMATE_E;
    }
    /*bool Physical::isPlaceholder() {
        return id == ID_PLACEHOLDER;
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
#pragma endregion BOOL_GET_SET
