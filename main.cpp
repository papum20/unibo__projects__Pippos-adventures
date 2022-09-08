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



		//// GESTIONE MENU APERTI CON INPUT
			// CONTROLLA SE È STATO PREMUTO UN TASTO PAUSA, MA APPLICALO SOLO SE È PRIMA STATO RILASCIATO (ALTRIMENTI IL MENU SI APRIREBBE E CHIUDEREBBE)
		if(pressedPause && inputManager->get_input() != KEY_PAUSE) pressedPause = false;
		if(pressedMinimap && inputManager->get_input() != KEY_PAUSE) pressedMinimap = false;

		//// MENU INIZIALE
		if(menu.is_active()) {
			if(frame % 2 == 0) mvwprintw(debug, 5, 1, "menu");

			menu.update(isRunning);
		}
		//// IN GIOCO
		else {
		//// GESTIONE MENU APERTI CON INPUT
			if(inputManager->get_input() == KEY_QUIT) isRunning = false;
			else if(inputManager->get_input() == KEY_MAIN_MENU) {
				menu.open();
			}
			else if(inputManager->get_input() == KEY_PAUSE) {
				if(!pressedPause) {
					if (!inventory.is_active()) inventory.open();
					else inventory.close();
					pressedPause = true;
				}
			}
			else if(inputManager->get_input() == KEY_QUIT) {
				if(!pressedMinimap) {
					if(!miniMap.isOpen()) miniMap.open(level);
					else miniMap.close();
					pressedMinimap = true;
				}
			}

			//// UPDATE
			if(inventory.is_active()) {
				if(frame % 2 == 0) mvwprintw(debug, 5, 1, "pause");

				if(!pressedPause) inventory.update(player, inputManager->get_input());
				else inventory.update(player, ERR);
			}
			else if(miniMap.isOpen()) {
				if(frame % 2 == 0) mvwprintw(debug, 5, 1, "map");
			}
			else {
				if(frame%2==0) mvwprintw(debug,5,1,"level");

				level.update(inputManager->get_input());
				level.display();
				hud.drawHud();
			}
		}


		//// DEBUG
		mvwprintw(debug,0,0,to_string(frame).c_str());
		mvwprintw(debug,1,0,to_string((int)game_timer.get_time_passed(GAME_TIMER_INDEX)).c_str());
		mvwprintw(debug,2,0,to_string((int)(frame / game_timer.get_time_passed(GAME_TIMER_INDEX))).c_str());
		mvwaddch(debug,3,0,inputManager->get_input());
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
