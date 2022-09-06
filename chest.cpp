#include "chest.hpp"

Chest::Chest() : Inanimate(){
    size = Coordinate(chest_width, chest_depth);
}

Chest::Chest(pWeapon w) : Inanimate(){
    arma=w;
    type='w';
    size = Coordinate(chest_width, chest_depth);
}

Chest::Chest(pArtifact a) : Inanimate(){
    artefatto=a;
    type='a';
    size = Coordinate(chest_width, chest_depth);
}

Chest::Chest(pItem_def d) : Inanimate(){
    item_def=d;
    type='d';
    size = Coordinate(chest_width, chest_depth);
}

void Chest::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
    if(!drawn) {
		Coordinate win_end = Coordinate(win_start, win_size);
		Coordinate local = Coordinate(0, 0, getCurrentAnimation().size);	//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(pos, win_start, win_end);	    //coordinata globale di relative, sulla mappa
			if(global.inOwnBounds() && animationMask(local))				//se il punto è interno alla finestra da disegnare e deve disegnare qualcosa
				scr[global.rel_int_y()][global.rel_int_x()] = Cell(getCurrentAnimation().state[local.single()], main_color, -1, CELL_NO_ATTR);
		} while(!local.equals(pos));
		drawn = true;
	}
}


pWeapon Chest::open_w(){
    return this->arma;
}

pArtifact Chest::open_a(){
    return this->artefatto;
}

pItem_def Chest::open_d(){
    return this->item_def;
}