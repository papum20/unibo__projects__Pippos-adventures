#include "animation.hpp"


Animation::Animation() {
    set({}, COORDINATE_ZERO, this);
}

Animation::Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size) {
    set(state, size, this);
}

Animation::Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, const int len) {
    if(len > 0) {
        set(animation[0], size, this);
        for(int i = 1; i < len; i++)
            tail_insert(animation[i], size);
    }
    else set({}, COORDINATE_ZERO, this);
}

void Animation::set(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, p_Animation next) {
    this->size = size;
    this->next = next;
    if(!size.equals_int(COORDINATE_ZERO)) {
        Coordinate i = Coordinate(COORDINATE_ZERO, ANIMATION_SIZE, COORDINATE_ZERO, size);
        do {
            Coordinate reverse = Coordinate(i.x, size.y - i.y - 1);
            this->state[reverse.single_set(ANIMATION_SIZE)] = state[i.inty()][i.intx()];
            i.next();
        } while(!i.equals(COORDINATE_ZERO));
    }
    index = ANIMATION_FIRST_INDEX;
}



void Animation::tail_insert(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], Coordinate size)
{
    p_Animation new_p = new Animation(state, size);
    p_Animation it = this;
    while(it->next != this) it = it->next;
    it->next = new_p;
    new_p->index = it->index + 1;
    new_p->next = this;       //lista circolare
}


void Animation::delete_list() {
	while(next != this) {
		p_Animation tmp = next;
        delete next;
        next = tmp;
	}
	delete this;
}

char Animation::at(Coordinate pos) {
    return state[pos.single_set(ANIMATION_SIZE)];
}
bool Animation::isLastFrame() {
    return next->index == ANIMATION_FIRST_INDEX;
}