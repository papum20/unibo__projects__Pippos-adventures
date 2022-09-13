#ifndef GENERAL_DEFINITIONS
#define GENERAL_DEFINITIONS



#include <curses.h>


//// REFRESH RATE : durata di un frame
#pragma region REFRESH_RATE
#define FRAMES_PER_SECOND 15					//aggiornamenti in un secondo
#define ANIMATIONS_PER_SECOND 6
#define REFRESH_RATE (1. / FRAMES_PER_SECOND)	//durata di un aggiornamento
#define REFRESH_TIMER_INDEX 0					//indice del timer (implementazione)
#define GAME_TIMER_INDEX 1
#pragma endregion REFRESH_RATE


#pragma region SCREENS_SIZES
// CAMERA
#define CAMERA_WIDTH  150//300//150//135	//larghezza (massima) inquadratura livello
#define CAMERA_HEIGHT 50//70//50//35		//altezza (massima) inquadratura livello
// MINI-MAP
#define MINIMAP_WIDTH (CAMERA_WIDTH - 4)
#define MINIMAP_HEIGHT (CAMERA_HEIGHT - 2)
#define MINIMAP_PADDING_X 4				//distanza da bordo sinistro e destro
#define MINIMAP_PADDING_Y 2
// INVENTORY
//space
const int n_max_inventory_objects = 26;
// SYSTEM_TEXT_WINDOW_CONSTANTS
#define WINDOW_TEXT_HEIGHT 11
#define WINDOW_TEXT_WIDTH 70
// FINESTRA DEBUG
#define DEBUG_WIDTH 13
#define DEBUG_HEIGHT 3
#define DEBUG_LENGTH (DEBUG_WIDTH + 1)
#define DEBUG_X 0
#define DEBUG_Y 0
const char DEBUG_WRITE_LEVEL[] = "livello    ";
const char DEBUG_WRITE_SECONDS[] = "    secondi";
const char DEBUG_WRITE_FPS[] = "        FPS";
#define DEBUG_Y_LEVEL 0
#define DEBUG_Y_SECONDS 1
#define DEBUG_Y_FPS 2
#define DEBUG_X_LEVEL 8
#define DEBUG_X_SECONDS 0
#define DEBUG_X_FPS 0
#define DEBUG_MAX_LEVEL 1000
#define DEBUG_MAX_SECONDS 1000
#define DEBUG_MAX_FPS 10000000
#pragma endregion SCREENS_SIZES



////LEVEL
#define LEVELS_N 3
////ROOM
#pragma region ROOM_DEFINITIONS
#define SCALE_X 8									//coefficiente di "allargamento orizzontale" della stanza
#define SCALE_Y 3
#define ROOM_WIDTH_T 30								//larghezza (senza scala) stanza
#define ROOM_WIDTH (ROOM_WIDTH_T * SCALE_X)//320	//larghezza (reale) stanza
#define ROOM_HEIGHT_T 20//180
#define ROOM_HEIGHT (ROOM_HEIGHT_T * SCALE_Y)//180
#define ROOM_BOSS_WIDTH 100
#define ROOM_BOSS_HEIGHT 40
#define ROOM_BOSS_WALL_DEPTH 3
#define ROOM_AREA_T (ROOM_WIDTH_T * ROOM_HEIGHT_T)
#define ROOM_AREA (ROOM_WIDTH * ROOM_HEIGHT)
#define CENTRAL_ROOM_WIDTH_T 9						//dimensioni dello spazio vuoto quadrato al centro (la width è prima dello scale)
#define CENTRAL_ROOM_HEIGHT_T 2
//CONNECTED ROOM
#define MAX_CONNECTED_R 5					//massimo numero di stanze collegate a ognuna
#define MAX_SIDES_R 4						//massimo numero di stanze (normali) collegate sui lati
//LEVEL
#define N_ROOMS 10							//numero di stanze (normali) generate per livello
#define LEVEL_AREA (N_ROOMS * N_ROOMS)		//dimensioni matrice livello
#pragma endregion ROOM_DEFINITIONS

//// COSTANTI PER LA RAPPRESENTAZIONE GRAFICA
#pragma region GRAPHICS
#define COLORS_NUMBER 8
// COLORI RIDEFINITI:
//COLOR_BLACK
//COLOR_WHITE
//COLOR_RED
//COLOR_GREEN
//COLOR_BLUE
#define COLOR_BROWN COLOR_MAGENTA
#define COLOR_BROWN_LIGHT COLOR_YELLOW
#define COLOR_GREY COLOR_CYAN
// COLORI ASSOCIATI:
#define COLOR_WALL COLOR_BROWN_LIGHT
#define COLOR_TRANSPARENT COLOR_BROWN		//per il muro quando diventa più chiaro se c'è qualcosa dietro
#define COLOR_WALL_TOP COLOR_BLACK			//bordo superiore muro
#define COLOR_WALL_BASE COLOR_BLACK			//bordo superiore muro
#define COLOR_FLOOR COLOR_GREEN
#define COLOR_SHADOW COLOR_GREY				//per il pavimento con l'ombra di un oggetto
#define COLOR_DOOR COLOR_BLUE
#define COLOR_OUTSIDE_FG COLOR_WHITE
#define COLOR_OUTSIDE_BG COLOR_BLACK

#define COLOR_PLAYER COLOR_WHITE
#define COLOR_WEAPON COLOR_BLUE
#define COLOR_PROJECTILE COLOR_BLUE
#define COLOR_ENEMY COLOR_RED
#define COLOR_CHEST COLOR_BLUE
// CARATTERI:
#define CHAR_EMPTY ' '
#define CHAR_WALL_BASE '_'
#define CHAR_WEAPON_MASK 'm'				//quando si trova questo carattere in un'animazione, in quel punto non verrà rappresentato il personaggio
#define CHAR_OUTSIDE '.'
// DIMENSIONI
#define WALL_HEIGHT 6
#define DOOR_HEIGHT (WALL_HEIGHT)
#define DOOR_WIDTH 4
#define DOOR_DEPTH 1
//player
const int p_width = 3;
const int p_height = 3;
const int p_depth = 2;
#pragma endregion GRAPHICS

//PLAYER
#define p_max_health 100
#define p_max_lives 5

//// COMANDI
#pragma region KEY_BINDINGS
const int esc = 27; //tasto per uscire dall'inventario
const int invio = 10; //serve nel menu di usa e scarta dell'oggetto per accettare 

const int scroll_up = KEY_UP;
const int scroll_down = KEY_DOWN;
const int scroll_left = KEY_LEFT;
const int scroll_right = KEY_RIGHT;
//apertura/utilzzo menu
#define KEY_PAUSE 'm'
#define KEY_ESC 'q'
#define KEY_MAIN_MENU 'p'
#define KEY_QUIT 'o'
#define KEY_MAP 'b'
#define KEY_SELECT_MENU invio
//gioco
#define KEY_INTERACT 'v'
#pragma endregion KEY_BINDINGS


#define ERROR_INT -1


//MESSAGGI DI SISTEMA
#define max_words 70
const char door_unlocked[max_words]={"PORTA SBLOCCATA"};
const char no_keys[max_words]={"CHIAVI INSUFFICIENTI"};
const char gain_life[max_words]={"HAI RIPRISTINATO PARTE DELLA TUA SALUTE"};
const char life_max[max_words]={"LA TUA SALUTE E' AL MASSIMO"};
const char gain_heart[max_words]={"HAI OTTENUTO UNA VITA IN PIU'"};
const char lose_heart[max_words]={"HAI PERSO UNA VITA"};
const char life_full[max_words]={"HAI RAGGIUNTO IL NUMERO MASSIMO DI VITE"};
const char no_weapon[max_words]={"NON PUOI PIU' RACCOGLIERE ARMI"};
const char no_item_difensive[max_words]={"NON PUOI PIU' RACCOGLIERE OGGETTI DIFENSIVI"};
const char no_artifacts[max_words]={"NON PUOI PIU' RACCOGLIERE ARTEFATTI"};
const char collect_weapon[max_words]={"HAI RACCOLTO UN'ARMA"};
const char collect_item_difensive[max_words]={"HAI RACCOLTO UN ITEM DIFENSIVO"};
const char collect_artifact[max_words]={"HAI RACCOLTO UN ARTEFATTO"};
const char collect_key[max_words]={"HAI RACCOLTO UNA CHIAVE"};
const char upgrade_equip[max_words]={"HAI MIGLIORATO UN OGGETTO NEL TUO EQUIPAGGIAMENTO"};
const char no_upgrade[max_words]={"NON PUOI MIGLIORARE NESSUN ALTRO OGGETTO DEL TUO EQUIPAGGIAMENTO"};
const char no_stamina[max_words]={"NON HAI STAMINA SUFFICIENTE PER ATTACCARE"};



#endif