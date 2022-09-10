#include "chest.hpp"

Chest::Chest() : Inanimate(){
    id = ID_CHEST;
    size = Coordinate(chest_width, chest_depth);
    idle_index = chest_idle_index;
    current_animation = idle_index;
    animations[chest_idle_index] = new Animation(chest_idle, Coordinate(chest_width, chest_height));
    animations_n = 1;
    main_color = COLOR_CHEST;
}

Chest::Chest(pKey k):Inanimate(){
    id=ID_CHEST;
    key=k;
    type='k';
    size = Coordinate(chest_width, chest_depth);
    idle_index = chest_idle_index;
    current_animation = idle_index;
    animations[chest_idle_index] = new Animation(chest_idle, Coordinate(chest_width, chest_height));
    animations_n = 1;
    main_color = COLOR_CHEST;
}

Chest::Chest(pWeapon w) : Inanimate(){
    id = ID_CHEST;
    arma=w;
    type='w';
    size = Coordinate(chest_width, chest_depth);
    idle_index = chest_idle_index;
    current_animation = idle_index;
    animations[chest_idle_index] = new Animation(chest_idle, Coordinate(chest_width, chest_height));
    animations_n = 1;
    main_color = COLOR_CHEST;
}

Chest::Chest(pArtifact a) : Inanimate(){
    id = ID_CHEST;
    artefatto=a;
    type='a';
    size = Coordinate(chest_width, chest_depth);
    idle_index = chest_idle_index;
    current_animation = idle_index;
    animations[chest_idle_index] = new Animation(chest_idle, Coordinate(chest_width, chest_height));
    animations_n = 1;
    main_color = COLOR_CHEST;
}

Chest::Chest(pItem_def d) : Inanimate(){
    id = ID_CHEST;
    item_def=d;
    type='d';
    size = Coordinate(chest_width, chest_depth);
    idle_index = chest_idle_index;
    current_animation = idle_index;
    animations[chest_idle_index] = new Animation(chest_idle, Coordinate(chest_width, chest_height));
    animations_n = 1;
    main_color = COLOR_CHEST;
}

void Chest::destroyInstance(pMap map) {
    if(type=='a') arma->destroyInstance(map);
    else if(type=='k') key->destroyInstance(map);
    else if(type =='d') item_def->destroyInstance(map);
    else if(type =='a') artefatto->destroyInstance(map);
    Inanimate::destroyInstance(map);
}

void Chest::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
    if(!drawn) {
		Coordinate win_end = Coordinate(win_start, win_size);
		Coordinate local = Coordinate(COORDINATE_ZERO, ANIMATION_SIZE, COORDINATE_ZERO, getCurrentAnimation().size);	//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(Coordinate(pos.integer(), local), win_start, win_end);    //coordinata globale di relative, sulla mappa
			if(global.inOwnBounds() && animationMask(local))            			    	        //se il punto è interno alla finestra da disegnare e deve disegnare qualcosa
				scr[global.rel_int_y()][global.rel_int_x()].edit(getCurrentAnimation().at(local), main_color, -1, CELL_NO_ATTR);
            local.next();
		} while(!local.equals(COORDINATE_ZERO));
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
