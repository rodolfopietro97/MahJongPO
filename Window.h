/*
 * Window.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Finestra di gioco
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>
using namespace std;

#include <allegro5/allegro.h>

#include "GameObject.h"
#include "GlobalValues.h"

class Window : public GameObject {

private:
	/*
	 * Display allegro associato alla finestra
	 */
	ALLEGRO_DISPLAY * display;

public:
	/*
	 * Costruttore di default
	 */
	Window() : GameObject(GlobalValues::getWindowWidth(), GlobalValues::getWindowHeight(), 0, 0){
		display = al_create_display(width, height);
		if (!display) {
			cout << "Impossibile inizializzare la finestra o gli eventi ad essa associati!";
			GlobalValues::stopGame();
		}
		else {
			al_set_window_title(display, GlobalValues::getWindowTitle().c_str());
			al_set_window_position(display, x, y);
			refresh();
		}
	}

	/*
	 * Distruttore
	 */
	~Window(){ al_destroy_display(display); }

	/*
	 * Metodo di aggiornamento della finestra
	 */
	void refresh(){
		Color c = GlobalValues::getWindowColor();
		al_resize_display(display, width, height);
		al_clear_to_color(al_map_rgba(c.red, c.green, c.blue, c.alpha));
	}

	/*
	 * Sleep
	 * @seconds di sleep
	 */
	void sleep(const double seconds) const { al_rest(seconds); }

	/*
	 * Flip del display di allegro
	 */
	void flip() const { al_flip_display(); }

	/*
	 * Setter e Getter
	 */
	ALLEGRO_DISPLAY* getDisplay(){ return this->display; }
};


#endif /* WINDOW_H_ */
