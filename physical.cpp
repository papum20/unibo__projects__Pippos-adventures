#include "physical.hpp"




Physical::Physical() {

}
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