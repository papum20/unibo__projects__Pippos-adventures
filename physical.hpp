#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP


#define ctrl(x) (x & 0x1F)				//permette di fare i controlli per le combinazioni ctrl+tasto per fare combo e simili.  
										//Es. if ( input==ctrl(a) ) permette di controllare se abbiamo premuto ctrl+a


#pragma region PHYSICAL_CONSTANTS

const int MAX_ANIMATIONS = 8;
// NUMERI
#define N_ENEMIES 6
#define N_PROJECTILES 4

#define N_CHEST_TYPES 3
#define N_ITEM_DIFENSIVO 5
#define N_ARTIFACTS 4
#define N_WEAPONS 5
#define N_ITEMS (N_ITEM_DIFENSIVO + N_ARTIFACTS + N_WEAPONS)

// ID
#pragma region PHYSICAL_IDS
#define ID_INANIMATE_S 10
#define ID_INANIMATE_E 19
#define ID_ENEMY_S 100
#define ID_ENEMY_E 149
#define ID_ITEM_S 150
#define ID_ITEM_E 179

#define ID_ARTIFACT_S 150
#define ID_ARTIFACT_POTION 151
#define ID_ARTIFACT_RUNE 152
#define ID_ARTIFACT_E 159

#define ID_WEAPON_S 160
#define ID_WEAPON_SWORD 161
#define ID_WEAPON_AXE 162
#define ID_WEAPON_BOW 163
#define ID_WEAPON_ROD 164
#define ID_WEAPON_E 169

#define ID_ITEM_DIFENSIVO_S 170
#define ID_ITEM_DIFENSIVO_ARMOR 171
#define ID_ITEM_DIFENSIVO_HELM 172
#define ID_ITEM_DIFENSIVO_BOOTS 173
#define ID_ITEM_DIFENSIVO_SHIELD 174
#define ID_ITEM_DIFENSIVO_NECKLACE 175
#define ID_ITEM_DIFENSIVO_E 179

#define ID_PROJECTILE_S 180
#define ID_PROJECTILE_E 189
#define ID_WEAPON_ENEMY_S 190
#define ID_WEAPON_ENEMY_E 199

#define ID_DEFAULT 0
#define ID_PLACEHOLDER 1
#define ID_PLAYER 2
#define ID_CHEST 3
#define ID_WALL 10
#define ID_FLOOR 11
#define ID_DOOR 12

#define ID_HEALTH_POTION 150
#define ID_KEY 151
#define ID_LIFE_ELIXIR 152
#define ID_RUNE 153

#define ID_SWORD 160
#pragma endregion PHYSICAL_IDS

#pragma region PHYSICAL_STATS
#define PHYSICAL_MAX_SPEED 5.
#pragma endregion PHYSICAL_STATS

#pragma endregion PHYSICAL_CONSTANTS


#include <iostream>
#include "animation.hpp"
#include "cell.hpp"
#include "coordinate.hpp"
#include "definitions.hpp"
#include "map.hpp"



class Physical {
	protected:
		Coordinate pos;
		Coordinate size;
		Coordinate speed;
		Coordinate lastMove;
		int id;			//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animations[MAX_ANIMATIONS]; //array di liste di array bidimensionali
		int animations_n;

		//BOOL DI CONTROLLO
		bool updated;
		bool drawn;		//mark se l'oggetto è stato disegnato per il frame corrente

		//// FUNZIONI AUSILIARIE
		//virtual void drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate pos, attr_t color);	//riempie una cella
		//precondizione: da richiamare con coordinate giuste, e con pos con matrice impostata

	public:
		int current_animation;
		
		Physical();
		void copyPhysical(Physical B);			//copia i parametri di B
		virtual void update(pMap map);			//da richiamare a ogni frame
		virtual void destroy(pMap map);
		virtual void destroyInstance(pMap map);	//distrugge tutto tranne le animazioni (per eliminare le istanze copiate)

		virtual void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		//precondizione: da richiamare con coordinate giuste, e con pos con matrice impostata
		void drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size);						//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra
		//precondizione: da richiamare con coordinate giuste

		// BOOL
		bool isInanimate();
		bool isCharacter();
		bool isProjectile();
		//bool isItem();			//se è item/artefatto...
		bool isWeapon();
		bool isItemDifensivo();
		bool isArtifact();
		bool isSword();
		bool isAxe();
		bool isBow();
		bool isRod();

		bool isArmor();
		bool isShield();
		bool isHelm();
		bool isBoots();
		bool isNecklace();

		bool isPotion();
		bool isRune();
		bool findInArray(Physical *A[ROOM_AREA], int len);
		virtual bool animationMask(Coordinate pos);			//true se la posizione, relativa all'animazione (partendo dal basso), copre quello che c'è sotto

		// GET
		int getId();
		Coordinate getPosition();
		Coordinate getSize();
		Coordinate getSpeed();				//velocità in caselle/secondo (float)
		Coordinate lastFrameMovement();
		Animation getCurrentAnimation();
		// SET
		void next_animation();
		void setPosition(Coordinate pos);
		void resetUpdate();					//rende non updated

};

typedef Physical *pPhysical;




#endif