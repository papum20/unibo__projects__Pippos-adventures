#include "animation.hpp"


Animation::Animation() {
    width = 0;
    height = 0;
    next = NULL;
}

Animation::Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            this->state[i][j] = state[i][j];
        }
    }
    this->width = width;
    this->height = height;
    this->next = this;
}

Animation::Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height, int len) {
    if(len > 0) {
        Animation(animation[0], width, height);
        int i = 1;
        while(i < len) {
            tail_insert(this, animation[i], width, height);
            i++;
        }
    }
    else Animation();
}



p_Animation Animation::tail_insert(p_Animation head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height)
{
    p_Animation new_p = new Animation(state, width, height);

    if(head == NULL) head = new_p;
    else{
        p_Animation it = head;
        while(it->next != head) it = it->next;
        it->next = new_p;
    }
    new_p->next = head;       //lista circolare
    
    return head;
}


void Animation::delete_list() {
	p_Animation p = next;
	while(next != this) {
		p_Animation tmp = p;
		p = p->next;
		delete tmp;
	}
	delete this;
}