#include "main.hpp"
using namespace std;






int main() {

	bool isRunning = true;
	bool pressedPause = false;
	bool pressedMinimap = false;

	Timer game_timer = Timer();
	game_timer.set_max(REFRESH_TIMER_INDEX, REFRESH_RATE);

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	
	//FINESTRE
	//calcolo per posizionare la finestra di gioco al centro
	int stdscr_x, stdscr_y;
	getmaxyx(stdscr, stdscr_y, stdscr_x);
	int level_x = (stdscr_x - CAMERA_WIDTH) / 2, level_y = (stdscr_y - (CAMERA_HEIGHT + HUD_HEIGHT + HUD_OFFSET)) / 2 + HUD_HEIGHT + HUD_OFFSET;
	int input_x = level_x + CAMERA_WIDTH, input_y = level_y + CAMERA_HEIGHT - input_h;
	int hud_x = (stdscr_x - HUD_WIDTH) / 2, hud_y = level_y - HUD_HEIGHT - HUD_OFFSET;
	int map_x = (stdscr_x - MINIMAP_WIDTH) / 2, map_y = (stdscr_y - MINIMAP_HEIGHT) / 2;

	//costruttori
	pInputManager inputManager = new InputManager(input_x, input_y);
	pPlayer player = new Player(inputManager);
	Level level = Level(level_x, level_y, player);

	Hud hud = Hud(hud_x, hud_y, player);
	Inventory inventory = Inventory(player, inputManager);
	Menu menu = Menu(inputManager);
	MiniMap miniMap = MiniMap(map_x, map_y);



	menu.open();
	


	WINDOW *debug = newwin(10,10,0,0);
	box(debug,0,0);
	wrefresh(debug);
	int frame = 0;
	game_timer.start(GAME_TIMER_INDEX);
	//// UPDATE: ESEGUITO A OGNI FRAME
	while (isRunning)
	{
		
		// GESTIONE TEMPO FRAME : si eseguono tutte le operazioni, poi nel prossimo update il tempo rimasto nel tempo di aggiornamento (refresh_rate)
		// il gioco rimane "inattivo", continuando solo a ricevere l'input (comunque almeno una volta)
		do{
			inputManager->calculate_input();
		}while(!game_timer.check(REFRESH_TIMER_INDEX));
		game_timer.start(REFRESH_TIMER_INDEX);


		// TERMINA IL GIOCO
		if(inputManager->get_input() == KEY_QUIT) isRunning = false;

		if(menu.is_active()) {
			menu.update(isRunning);
		}

		else {
			// CONTROLLA SE È STATO PREMUTO UN TASTO PAUSA, MA APPLICALO SOLO SE È PRIMA STATO RILASCIATO (ALTRIMENTI IL MENU SI APRIREBBE E CHIUDEREBBE)
			if(pressedPause) {
				if(inputManager->get_input() != KEY_PAUSE) pressedPause = false;
			} else if(pressedMinimap) {
				if(inputManager->get_input() != KEY_MAP) pressedMinimap = false;
			} else if(inputManager->get_input() == KEY_PAUSE) {
				if(!inventory.is_active()) {
					//erase();
					//refresh();
					inventory.open();
					pressedPause = true;
				}
			} else if(inputManager->get_input() == KEY_MAP) {
				if(miniMap.isOpen()) miniMap.close();
				else miniMap.open(level);
				pressedMinimap = true;
			}

			//// IN PAUSA
			if (inventory.is_active()) {
				if(frame%2==0) mvwprintw(debug,5,1,"menu");
				else mvwprintw(debug,5,1,"     ");
				if(pressedPause) inventory.update(player, ERR);			//se il menu è aperto il player non si muove
				else {
					inventory.update(player, inputManager->get_input());
					if(inputManager->get_input() == KEY_PAUSE) pressedPause = true;
				}
			}
			//// IN GIOCO
			else {
				if(frame%2==0) mvwprintw(debug,5,1,"level");
				else mvwprintw(debug,5,1,"     ");
				if(inputManager->get_input() == KEY_PAUSE) {
					mvwaddch(debug,1,0,'P');
				}
				else mvwaddch(debug,1,0,'p');// menu.open();

				level.update(inputManager->get_input());
				level.display();
				hud.drawHud();
			}
		}

		mvwprintw(debug,0,0,to_string(frame).c_str());
		mvwprintw(debug,2,0,to_string((int)game_timer.get_time_passed(GAME_TIMER_INDEX)).c_str());
		mvwprintw(debug,1,0,to_string((int)(frame / game_timer.get_time_passed(GAME_TIMER_INDEX))).c_str());
		wrefresh(debug);
		frame++;
	}


	//// END
	cursesEnd();
	gameEnd();
	
}





#pragma region FUNZIONI
void cursesInit() {
	initscr();			//inizializza schermo ncurses
	start_color();		//inizializza colori
}
void gameInit() {
	srand(time(NULL));
	colorsInit();
}
void colorsInit() {
	Cell::initPairs();
	init_color(COLOR_BROWN, 350, 100, 90);
	init_color(COLOR_BROWN_LIGHT, 500, 150, 150);
	init_color(COLOR_GREY, 100, 90, 80);
	init_color(COLOR_GREEN, 1, 230, 1);
	//init_color(COLOR_BLUE, 2, 500, 999);
	init_color(COLOR_RED, 900, 1, 1);
}

void cursesEnd() {
	endwin();			//dealloca memoria
}
void gameEnd() {
	delete FLOOR_INSTANCE;
	delete WALL_INSTANCE;
}
#pragma endregion FUNZIONI
