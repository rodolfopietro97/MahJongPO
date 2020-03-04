/*
 * Event.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Classe che gestisce gli eventi
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "GameObject.h"
#include <allegro5/allegro.h>
#include <iostream>
using namespace std;

class Event {

private:
	/*
	 * Stato del mouse
	 */
	ALLEGRO_MOUSE_STATE mouseState;
	/*
	 * Coda degli eventi
	 */
	ALLEGRO_EVENT_QUEUE *event_queue = 0;
	/*
	 * Singolo evento di allegro
	 */
	ALLEGRO_EVENT ev;
	/*
	 * Timeout degli eventi
	 */
	ALLEGRO_TIMEOUT timeout;

public:
	/*
	 * Costruttore Parametrizato
	 * @param display di gioco (Serve ad allegro per inizializzare la coda degli eventi)
	 */
	Event(ALLEGRO_DISPLAY *display) {
		event_queue = al_create_event_queue();
		if (!event_queue) {
			cout << "Impossibile inizializzare la coda di eventi!";
			GlobalValues::stopGame();
		} else {
			al_register_event_source(event_queue,
					al_get_display_event_source(display));
		}
	}

	/*
	 * Distruttore
	 */
	~Event() {
		al_destroy_event_queue(event_queue);
	}

	/*
	 * Restituisce la cordinata x del mouse
	 */
	int getMouseX() {
		al_get_mouse_state(&mouseState);
		return mouseState.x;
	}

	/*
	 * Restituisce la cordinata y del mouse
	 */
	int getMouseY() {
		al_get_mouse_state(&mouseState);
		return mouseState.y;
	}

	/*
	 * Ci dice se il mouse è stato premuto
	 */
	bool isMouseClicked() {
		al_get_mouse_state(&mouseState);
		return mouseState.buttons & ALLEGRO_EVENT_MOUSE_BUTTON_DOWN;
	}

	/*
	 * Ci dice se il mouse è stato rilasciato
	 */
	bool isMouseRelased() {
		al_get_mouse_state(&mouseState);
		return mouseState.buttons & ALLEGRO_EVENT_MOUSE_BUTTON_UP;
	}

	/*
	 * Ci dice se è stato cliccato il bottone di chiusura della finestra
	 */
	bool onGameClose() {
		al_init_timeout(&(Event::timeout), 0.01);
		bool get_event = al_wait_for_event_until(Event::event_queue,
				&(Event::ev), &(Event::timeout));
		return (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE);
	}

	/*
	 * Ci dice se si è passati con il mouse sopra un Oggetto
	 * @param o oggetto su cui si deve verificare se si è passati con il mouse
	 */
	bool hover(GameObject *o) {
		return getMouseX() >= o->getX()
				&& getMouseX() <= (o->getX() + o->getWidth())
				&& getMouseY() >= o->getY()
				&& getMouseY() <= (o->getY() + o->getHeight());
	}

	/*
	 * Ci dice se si ha cliccato con il mouse un Oggetto
	 * @param o oggetto su cui si deve verificare se è stato cliccato con il mouse
	 */
	bool click(GameObject *o) {
		return hover(o) && isMouseClicked();
	}

	/*
	 * Ci dice se c' stata una collisione sull' asse X tra due oggetti
	 * @param o1 primo oggetto
	 * @param o2 secondo oggetto
	 * @return se è avvenuta una collisione sull' asse X tra i due oggetti
	 */
	bool xCollision(GameObject *o1, GameObject *o2) {
		bool collision = false;
		for (float i = o1->getX();
				i <= o1->getX() + o1->getWidth() && !collision; i++)
			for (float j = o2->getX();
					j <= o2->getX() + o2->getWidth() && !collision; j++)
				if (i == j)
					collision = true;

		return collision;
	}

	/*
	 * Ci dice se c' stata una collisione sull' asse Y tra due oggetti
	 * @param o1 primo oggetto
	 * @param o2 secondo oggetto
	 * @return se è avvenuta una collisione sull' asse Y tra i due oggettti
	 */
	bool yCollision(GameObject *o1, GameObject *o2) {
		bool collision = false;
		for (float i = o1->getY();
				i <= o1->getY() + o1->getHeight() && !collision; i++)
			for (float j = o2->getY();
					j <= o2->getY() + o2->getHeight() && !collision; j++)
				if (i == j)
					collision = true;

		return collision;
	}

	/*
	 * Ci dice se c' stata una collisione tra due oggetti
	 * @param o1 primo oggetto
	 * @param o2 secondo oggetto
	 * @return se è avvenuta una collisione tra i due oggetti
	 */
	bool collision(GameObject *o1, GameObject *o2) {
		return xCollision(o1, o2) && yCollision(o1, o2);
	}

};


#endif /* EVENT_H_ */
