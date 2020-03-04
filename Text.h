/*
 * Text.h
 *
 *  Created on: 27 apr 2018
 *      Author: rodolfo
 *
 *  Classe che rappresenta un testo (una stringa disegnabbile)
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Sprite.h"
#include "Color.h"

using namespace std;

class Text : public Sprite{

private:
	/*
	 * Font del testo
	 */
	ALLEGRO_FONT *font;

	/*
	 * Dimensione del testo/font (inizializzabile una volta solla)
	 */
	unsigned fontSize;

	/*
	 * Ci dice se il testo è centrato o meno
	 */
	bool centred;

	/*
	 * Colore del testo/font
	 */
	Color color;

	/*
	 * Testo/stringa
	 */
	string text;

public:
	/*
	 * Costruttore Parametrizzato
	 * @param path del testo
	 * @param fontSize del testo
	 * @param text stringa da disegnare (contenuto)
	 * @param color del testo
	 * @param x del testo
	 * @param y del testo
	 * @param centred se il testo deve essere allineato centrato o meno
	 */
	Text(string path, unsigned fontSize, string text, Color color, float x, float y, bool centred) :
			Sprite(0, 0, x, y, path), fontSize(fontSize), text(text), color(color), centred(centred) {

		font = al_load_ttf_font((GlobalValues::getAssetPath() + path).c_str(), fontSize, 0);
		if (!font) {
			cout << "Impossibile inizializzare il testo!";
			GlobalValues::stopGame();
		}
	}

	/*
	 * Setter e Getter
	 */
	bool isCentred() const {
		return centred;
	}

	void setCentred(bool centred) {
		this->centred = centred;
	}

	Color getColor() const {
		return color;
	}

	void setColor(Color color) {
		this->color = color;
	}

	ALLEGRO_FONT* getFont() {
		return font;
	}

	int getFontSize() const {
		return fontSize;
	}

	const string& getText() const {
		return text;
	}

	void setText(const string& text) {
		this->text = text;
	}
};



#endif /* TEXT_H_ */
