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



#pragma region AUSILIARIE

p_Animation Physical::tail_insert(p_Animation head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height)
{
    p_Animation tmp = new Animation;
    for(int i=0; i <height; i++){
        for(int j=0; j < width; j++){
            tmp->state[i][j] = state[i][j];
        }
    }
    tmp->width = width;
    tmp->height = height;

    if(head==NULL) head = tmp;
    else{
        p_Animation tmp1 = head;
        while(tmp1->next != head) tmp1 = tmp1->next;
        tmp1->next = tmp;
    }
    tmp->next = head;       //lista circolare
    
    return(head);
}

#pragma endregion AUSILIARIE

#pragma region BOOL_GET_SET
    bool Physical::isInanimate() {
        return id >= ID_INANIMATE_S && id <= ID_INANIMATE_E;
    }
    bool Physical::isPlaceholder() {
        return id == ID_PLACEHOLDER;
    }
    int Physical::getId() {
        return id;
    }
    Coordinate Physical::getPosition() {
        return pos;
    }
#pragma endregion BOOL_GET_SET
