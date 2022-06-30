#include "physical.hpp"




Physical::Physical() {
        id = DEFAULT_ID;
    }

void Physical::drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos) {

}
void Physical::drawAtOwnPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size) {
    drawAtPosition(scr, win_size, {xPos, yPos});
}



#pragma region AUSILIARIE
p_Animation Physical::tail_insert(p_Animation head, const char state[][ANIMATION_WIDTH], int width, int height) {
    if(head==NULL)
    {
        //char state[ANIMATION_HEIGHT][ANIMATION_WIDTH]
        head = new Animation;
        for(int i=0; i <ANIMATION_HEIGHT; i++){
            for(int j=0; j < ANIMATION_WIDTH; j++){
                head->state[i][j] = state[i][j];
            }
        }

        head->height = height;
        head->width = width;
        head->next = head; //lista circolare
        return (head);
    }
    else{
        p_Animation tmp = new Animation;
        tmp->next = head;
        tmp->width = width;
        tmp->height = height;
        for(int i=0; i <ANIMATION_HEIGHT; i++){
            for(int j=0; j < ANIMATION_WIDTH; j++){
                tmp->state[i][j] = state[i][j];
            }
        }
        p_Animation tmp1 = head;
        while(!(tmp1->next==head))
            tmp1=tmp1->next;
        tmp1->next=tmp;
        return(head);
    }
}
#pragma endregion AUSILIARIE

#pragma region BOOL_GET_SET
    bool Physical::isInanimate() {
        return id >= INANIMATE_ID_S && id <= INANIMATE_ID_E;
    }
    int Physical::getId() {
        return id;
    }
    void Physical::getPosition(Coordinate &out) {
        out = {xPos, yPos};
    }
#pragma endregion BOOL_GET_SET
