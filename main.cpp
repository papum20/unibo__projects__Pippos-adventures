#include "main.hpp"
using namespace std;






int main() {

	bool isRunning = true;
	bool in_mainMenu = true;
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
	int hud_x = ((stdscr_x - HUD_WIDTH) / 2)- WINDOW_TEXT_WIDTH/2, hud_y = level_y - HUD_HEIGHT - HUD_OFFSET;
	int map_x = (stdscr_x - MINIMAP_WIDTH) / 2, map_y = (stdscr_y - MINIMAP_HEIGHT) / 2;

	//costruttori

	System_text *text = new System_text(hud_x+HUD_WIDTH+1, hud_y-2);
	pInputManager inputManager = new InputManager(input_x, input_y);
	pPlayer player = new Player(inputManager, text);
	pLevel level = new Level(level_x, level_y, player);	

	Hud *hud = new Hud(hud_x, hud_y, player);
	MiniMap *miniMap = new MiniMap(map_x, map_y, level);
	Start_menu *main_menu = new Start_menu(stdscr_x, stdscr_y);
	Pause_menu  *pause_menu = new Pause_menu(player,stdscr_x, stdscr_y);
	Game_over game_over = Game_over(stdscr_x, stdscr_y);

	
	main_menu->open();
	
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
		if(pressedMinimap && inputManager->get_input() != KEY_MAP) pressedMinimap = false;

		//// MENU INIZIALE
		if(main_menu->is_active()) {
			if(frame % 2 == 0) mvwprintw(debug, 5, 1, "menu ");

			main_menu->update(isRunning, inputManager->get_input());
		}
		//// IN GIOCO
		else {
			// SE IL MENU INIZIALE È APPENA STATO CHIUSO
			if(in_mainMenu) {
				level->open();
				in_mainMenu = false;
			}
		//// GESTIONE MENU APERTI CON INPUT
			if(inputManager->get_input() == KEY_QUIT) isRunning = false;
			else if(inputManager->get_input() == KEY_MAIN_MENU) {
				main_menu->open_over(level);
				hud->close();
				in_mainMenu = true;
				pressedMinimap = false, pressedPause = false;
			}
			else if(inputManager->get_input() == KEY_PAUSE) {
				if(!pressedPause) {
					if (!pause_menu->is_active()) pause_menu->open();
					else level->open_over(pause_menu);
					pressedPause = true;
				}
			}
			else if(inputManager->get_input() == KEY_MAP) {
				if(!pressedMinimap) {
					if(!miniMap->isOpen()) miniMap->open();
					else level->open_over(miniMap);
					pressedMinimap = true;
				}
			}

			//// UPDATE
			if(!in_mainMenu) {
				if(pause_menu->is_active()) {
					if(frame % 2 == 0) mvwprintw(debug, 5, 1, "pause");

					if(!pressedPause) pause_menu->update(inputManager->get_input());
					else pause_menu->update(ERR);
				}
				else if(miniMap->isOpen()) {
					if(frame % 2 == 0) mvwprintw(debug, 5, 1, "map  ");
				}
				else {
					if(frame%2==0) mvwprintw(debug,5,1,"level");

					level->update(inputManager->get_input());
					level->display();
					hud->drawHud();
					text->open();
				}
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
	//DELETE
	//hud->destroy();
	//inputManager->destroy();
	level->destroy();
	//main_menu->destroy();
	//miniMap->destroy();
	//pause_menu->destroy();
	//text->destroy();
	
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
	//// DELETE
	FLOOR_INSTANCE->destroy(NULL);
	WALL_INSTANCE->destroy(NULL);
}
#pragma endregion FUNZIONI
