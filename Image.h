/*
 * Image.h
 *
 *  Created on: 23 apr 2018
 *      Author: rodolfo
 *
 *  Classe che rappresenta un'immagine (un' immagine è uno Sprite)
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "Sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <string>
using namespace std;

class Image : public Sprite {

private:
	/*
	 * Immagine
	 */
	ALLEGRO_BITMAP *immagine;

	/*
	 * Dimensioni originali dell'immagine
	 */
	float originalWidth, originalHeight;

public:
	/*
	 * Costruttore vuoto per creare successivamente la matrice di Tessere
	 */
	Image(){}

	/*
	 * Costruttore Parametrizzato
	 * @param display della finestra da passare per disegnare correttamente l' immagine (serve ad allegro)
	 * @param path dell' immagine
	 * @param originalWidth dell' immagine (serve per al_draw_scaled_bitmap())
	 * @param originalHeight dell' immagine (serve per al_draw_scaled_bitmap())
	 * @param width dell' immagine (scalata)
	 * @param height dell' immagine (scalata)
	 * @param x dell' immagine
	 * @param y dell' immagine
	 */
	Image(ALLEGRO_DISPLAY *display, string path, float originalWidth, float originalHeight, float width, float height, float x, float y) :
		Sprite(width,height,x,y, path),
		originalWidth(originalWidth),
		originalHeight(originalHeight) {

		immagine = al_load_bitmap((GlobalValues::getAssetPath() + path).c_str());

		if (!immagine) {
			cout << "Impossibile caricare l' immagine";
			GlobalValues::stopGame();
		}

		al_set_target_bitmap(al_get_backbuffer(display));
		al_flip_display();
	}

	/*
	 * Setter e Getter
	 */
	/*
	 * Getter dell' immagini, servirà allo SpriteDraw successivamente
	 */
	ALLEGRO_BITMAP* getImmagine() { return immagine; }

	float getOriginalHeight() const {
		return originalHeight;
	}

	float getOriginalWidth() const {
		return originalWidth;
	}
};

#endif /* IMAGE_H_ */
