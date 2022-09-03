#include "chest.hpp"

Chest::Chest(){
    
}

Chest::Chest(pWeapon w){
    arma=w;
    type='w';
}

Chest::Chest(pArtifact a){
    artefatto=a;
    type='a';
}

Chest::Chest(pItem_def d){
    item_def=d;
    type='d';
}

void Chest::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
    if(!drawn) {
		Coordinate win_end = Coordinate(win_start, win_size);
		Coordinate local = Coordinate(0, 0, getCurrentAnimation().size);	//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(pos, win_start, win_end);	    //coordinata globale di relative, sulla mappa
			if(global.inOwnBounds() && animationMask(local))				//se il punto è interno alla finestra da disegnare e deve disegnare qualcosa
				scr[global.rel_int_y()][global.rel_int_x()] = Cell(getCurrentAnimation().state[local.single()], main_color, -1, -1);
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