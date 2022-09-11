#ifndef ROOM_HPP
#define ROOM_HPP


#include "coordinate.hpp"
#include "definitions.hpp"


//per ogni indice i, DIR_CHANCES[i] è la probabilità di generare i percorsi a partire da un punto (nella generazione della stanza);
//la prima posizione indica la probabilità di generare in 0 nuove direzioni (cioè di fermarsi)
const int DIR_CHANCES[DIRECTIONS_N + 1] = {5, 20, 10, 3, 1};
//COSTANTI PER MAKECONNECTION(): PER QUALI PORTE BLOCCARE CON CHIAVE
#define LOCKED_DOORS_MAX 1		//massimo numero di porte bloccate da chiave in una stanza
typedef char lock_type;
#define LOCK_TYPES_N 4			//numero di stati
#define LOCK_NONE	(lock_type)0
#define LOCK_OWN	(lock_type)1
#define LOCK_OTHER	(lock_type)2
#define LOCK_BOTH	(lock_type)3

// SPAZI
const Coordinate ZONE_DOOR_UD = Coordinate(SCALE_X*2, SCALE_Y);		//zona in cui non possono spawnare muri di fronte alla porta (up-down)
const Coordinate ZONE_DOOR_LR = Coordinate(SCALE_X, SCALE_Y*2);		//left-right
const Coordinate SPAWN_DISTANCE = Coordinate(40, 14);				//distanza dal player in cui non possono spawnare nemici


#include "map_handler.hpp"
#include "structures/union_find.hpp"

#include "enemy.hpp"
#include "enemies/enemies.hpp"
#include "equipment/equipment.hpp"
#include "items/artifacts.hpp"


//SPAWN: istanze e probabilità
//enemy
const int ENEMIES_N[LEVELS_N] {3, 10, 10};
const Enemy ENEMIES_INSTANCES[LEVELS_N][N_ENEMIES]		= 	{
															{Zombie(), Spider()},
															{Zombie(), Spider(), Fire_spirit(), Snowman(), Witch()},
															{Spider(), Fire_spirit(), Snowman(), Witch(), Evil_tree()}
															};
const int ENEMIES_CHANCHES[LEVELS_N][N_ENEMIES]			= 	{
															{3, 1},
															{2, 3, 4, 1, 1},
															{1, 2, 4, 4, 1}
															};
const int ENEMIES_CHANCE_TOT[LEVELS_N] = {4, 11, 12};
const int BOSSES_N[LEVELS_N] {15, 6, 3};
const Enemy BOSSES_INSTANCES[LEVELS_N][N_ENEMIES]	= 	{
															{Zombie()},
															{Snowman()},
															{Evil_tree()}
															};
const int BOSSES_CHANCHES[LEVELS_N][N_ENEMIES]	= 	{
															{1},
															{1},
															{1}
															};
const int BOSSES_CHANCE_TOT[LEVELS_N] = {1, 1, 1};
//item
const int CHESTS_N_MIN[LEVELS_N] {0, 0, 0};
const int CHESTS_N_MAX[LEVELS_N] {2, 2, 2};
#define ARTIFACT_INSTANCES_N (N_ARTIFACTS - 1)
#define ITEM_DIFENSIVO_INSTANCES_N (N_ITEM_DIFENSIVO)
#define WEAPON_INSTANCES_N (N_WEAPONS - 1)
#define ITEMS_INSTANCES_N (ARTIFACT_INSTANCES_N + ITEM_DIFENSIVO_INSTANCES_N + WEAPON_INSTANCES_N)
const Artifact ARTIFACT_INSTANCES[ARTIFACT_INSTANCES_N] = {HealthPotion(), Life_elixir(), Rune()};
const item_difensivo ITEM_DIFENSIVO_INSTANCES[ITEM_DIFENSIVO_INSTANCES_N] = {armor(), boots(), helm(), necklace(), shield()};
const Weapon WEAPON_INSTANCES[WEAPON_INSTANCES_N] = {Ascia(), Arco(), Player_Rod(), sword()};



class Room {
	private:
		Coordinate pos;												//coordinate rispetto alla prima stanza del livello

		//// FUNZIONI
		int chestsNumber(int level);								//numero di chest da spawnare in una stanza
		pChest randChest();
		virtual pEnemy randEnemy(int level, pCharacter player);		//ritorna un nemico casuale
		//// FUNZIONI AUSILIARIE
		int getFreeCells(s_coord available[], Coordinate size);							//modifica l'array con le celle disponibili per lo spawn di qualcosa di dimensione size e ne ritorna il numero
		// ADD
		void addChest(pChest obj);														//aggiunge una chest nella sua posizione
		// FUNZIONI AUSILIARIE DI GENERAZIONE - SECONDARIE
		void generatePath(Coordinate s, pUnionFind sets);								//genera un percorso casuale a partire da x,y
		int getAdjacentWalls(Coordinate out[], UnionFind sets, s_coord currentParent);	//riempie out con i muri adiacenti a una casella del set e ne ritorna il numero; PRECONDIZIONE: currentParent è parent del suo set
		int getBorderWalls(Coordinate walls[], int directions[], int walls_n, UnionFind sets, s_coord parent, int distance);
					//riempie walls, già contenente i muri adiacenti, con i soli muri di confine tra il set di parent e un altro (con spessore distance)
					//e directions con le rispettive direzioni; ne ritorna il numero
	protected:
		Coordinate size;		//dimensioni effettive
		Coordinate size_t;		//dimensioni senza l'allargamento scale_x
		Coordinate scale;		//ridimensionamento
		pMap map;

		//// FUNZIONI
		void addCharacter(pCharacter obj);							//aggiunge un character nella sua posizione
		// FUNZIONI AUSILIARIE
		int doorDirection(pDoor door);													//direzione in cui si trova la porta
		// SPAWN
		void spawnChest(pChest chest);							//spawna una chest
		void spawnEnemy(pEnemy enemy);							//spawna un nemico
		// FUNZIONI AUSILIARIE DI GENERAZIONE - PRINCIPALI
		void generateSidesWalls();
		void generateInnerRoom(pUnionFind sets);
		void generateAllPaths(pUnionFind sets);
		void connectPaths(pUnionFind sets);		//fa in modo che ogni punto sia raggiungibile da ogni altro
		void resizeMap();						//ridimensiona la mappa, allargando quella temporanea generata di X_SCALE


	public:
		Room(Coordinate pos);
		virtual void destroy();									//elimina tutti i puntatori contenuti nella stanza, agendo poi ricorsivamente sulle stanze collegate
		virtual void update(int input);							//da richiamare a ogni frame; chiama l'update di ogni elemento nella stanza
		
		virtual void generate(); 								//genera uno schema randomico per i muri, inserendoli nell'array map
		virtual void spawn(int level, pCharacter player, bool current = false);
		
		// DISEGNO
		void draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center);	//riempie l'array con le informazioni per stampare a schermo, con opportune modifiche di prospettiva e altro;
																									//inquadra solo un rettangolo con le dimensioni dei parametri intorno al giocatore

		// GET
		Coordinate getPos();
		Coordinate getSize();
		//pMap getMap();
		pDoor getDoor(int dir);										//porta in direzione
		virtual Coordinate getEntrance(pDoor door);					//posizione in cui si entra nell'altra stanza attraversando questa porta
		virtual Room *getConnectedRoom(pDoor door);					//ritorna il puntatore alla stanza collegata dalla porta
		virtual bool isBossRoom();

		// SET
		void remove(pPhysical obj);															//rimuove da map
		bool addCharacter_strong(pCharacter obj);											//posiziona obj in pos e, se lo spazio risulta occupato, sposta ciò che lo occupa (esclusi muri)
		virtual void makeConnection(Room *room, int dir, lock_type lt, bool first = true);	//collega l'altra stanza a questa (se è connectedRoom), con stato bloccato lt; first inizializzato da solo
		virtual void unlockDoor(pDoor door);												//sblocca porta da entrambi i lati

		//funzioni di debug: stampano la stanza in caratteri (rispettivamente con size e size_t)
		//void debug();
		//void debug2();
};



typedef Room *pRoom;


#include "math.hpp"

#include "physical.hpp"
#include "character.hpp"

#include "enemies/enemies.hpp"
#include "items/artifacts.hpp"
#include "equipment/equipment.hpp"
#include "floor.hpp"
#include "wall.hpp"
#include "chest.hpp"


#endif