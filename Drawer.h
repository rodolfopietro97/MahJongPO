/*
 * Drawer.h
 *
 *  Created on: 23 apr 2018
 *      Author: rodolfo
 *
 * Classe adibita al disegno degli Sprites
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include "Image.h"
#include "Text.h"
#include "Tessera.h"

class Drawer{

private:
	/*
	 * Immagine che si andrà a disegnare (se si vuole)
	 * quando si passa il mouse sopra
	 */
	Image *hover;

public:
	/*
	 * Costruttore Parametrizzato
	 * @param h immagine da disegnare se si passa sopra con il mouse
	 */
	Drawer(Image &h) { hover = &h; }

	/*
	 * Disegna un' immagine
	 * @param img da disegnare
	 */
	void drawImage(Image &img){
		al_draw_scaled_bitmap(img.getImmagine(),
				0,
				0,
				img.getOriginalWidth(),
				img.getOriginalHeight(),
				img.getX(),
				img.getY(),
				img.getWidth(),
				img.getHeight(),
				0);
	}

	/*
	 * Disegna un' immagine Hover (su cui per esempio è passato sopra il mouse)
	 * @param img da "hoverare"
	 */
	void drawImageHover(Image &img){
		al_draw_scaled_bitmap(hover->getImmagine(),
				0,
				0,
				10,
				10,
				img.getX(),
				img.getY(),
				img.getWidth(),
				img.getHeight(),
				0);
	}

	/*
	 * Disegna  un testo
	 * @param txt da disegnare
	 */
	void drawText(Text txt) {
		al_draw_text(txt.getFont(),
				al_map_rgb(txt.getColor().red, txt.getColor().green,
						txt.getColor().blue), txt.getX(), txt.getY(),
				txt.isCentred() ? ALLEGRO_ALIGN_CENTRE : ALLEGRO_ALIGN_LEFT,
				txt.getText().c_str());
	}

	/*
	 * Disegna una tessera (Ovviamente se non è stata cancellata!)
	 * @param t, tessera da disegnare
	 */
	void drawTessera(Tessera &t){
		if(!t.isCancellata()){
			al_draw_scaled_bitmap(t.getImmagine(),
					0,
					0,
					t.getOriginalWidth(),
					t.getOriginalHeight(),
					t.getX(),
					t.getY(),
					t.getWidth(),
					t.getHeight(),
					0);
		}
	}

	/*
	 * Disegna una tessera passata con il mouse(Ovviamente se non è stata cancellata!)
	 * @param t, tessera da disegnare
	 */
	void drawTesseraHover(Tessera &t){
		if(!t.isCancellata()){
			al_draw_scaled_bitmap(hover->getImmagine(),
					0,
					0,
					10,
					10,
					t.getX(),
					t.getY(),
					t.getWidth(),
					t.getHeight(),
					0);
		}
	}
};


#endif /* DRAWER_H_ */
