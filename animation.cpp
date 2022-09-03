#include "animation.hpp"


Animation::Animation() {
    size = Coordinate(0, 0);
    next = NULL;
}

Animation::Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size) {
    Coordinate i = Coordinate(0, 0, size);
    do {
        this->state[i.single()] = state[i.inty()][i.intx()];
        i.next();
    } while(!i.equals(COORDINATE_ZERO));
    this->size = size;
    this->next = this;
}

Animation::Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, const int len) {
    if(len > 0) {
        Animation(animation[0], size);
        int i = 1;
        while(i < len) {
            tail_insert(this, animation[i], size);
            i++;
        }
    }
    else Animation();
}



p_Animation Animation::tail_insert(p_Animation head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], Coordinate size)
{
    p_Animation new_p = new Animation(state, size);

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