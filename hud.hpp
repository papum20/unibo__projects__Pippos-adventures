#ifndef HUD_HPP
#define HUD_HPP


class Hud {
	private:

	public:
		Hud();
		//costruttore
		void drawHud();		//disegna hud (in gioco)
		void startMenu();	//inizializza il menu (quando si preme il tasto pausa)
		void updateMenu();	//disegna menu (solo se in pausa)
};





#endif