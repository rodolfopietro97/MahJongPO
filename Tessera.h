/*
 * Tessera.h
 *
 *  Created on: 27 apr 2018
 *      Author: rodolfo
 *
 *  Classe che rappresenta una tessera (Una tessera è un' immagine).
 */

#ifndef TESSERA_H_
#define TESSERA_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Image.h"

/*
 * Tipologia della tessera
 */
enum TIPOLOGIA { CERCHI = 0, BAMBU, CARATTERI, VENTI, DRAGHI, FIORI, STAGIONI };

class Tessera : public Image {

private:
	/*
	 * Riga e colonna della tessera nella matrice di gioco
	 */
	unsigned riga, colonna;

	/*
	 * Id della tessera
	 */
	unsigned id;

	/*
	 * Ci dice se la tessera è stata cancellata o no
	 */
	bool cancellata;

	/*
	 * Tipologia della tessera
	 */
	TIPOLOGIA tipo;

public:
	/*
	 * Costruttore parametrizzato
	 * @param display della finestra corrente
	 * @param id della tessera (che ne distingue univocamente la tessera)
	 * @param riga della tessera (per rappresentarla sulla matrice)
	 * @param colonna della tessera (per rappresentarla sulla matrice)
	 */
	Tessera(ALLEGRO_DISPLAY *display, unsigned id, unsigned riga,
			unsigned colonna, TIPOLOGIA tipo) :
				id(id),
				riga(riga),
				colonna(colonna),
				tipo(tipo),
				Image(display, "t" + to_string(id) + ".png",
				GlobalValues::getOriginalWidthTessera(),
				GlobalValues::getOriginalHeightTessera(),
				GlobalValues::getScaledWidthTessera(),
				GlobalValues::getScaledHeightTessera(),
				GlobalValues::getMatrixX() + colonna*(GlobalValues::getScaledWidthTessera()/2),
				GlobalValues::getMatrixY() + riga*(GlobalValues::getScaledHeightTessera()/2)){


		cancellata = false;

	}

	/*
	 * "Cancella una tessera" ovver non permette di disegnarla
	 */
	inline void cancellaTessera() { cancellata = true; }

	/*
	 * Restituisce la profondità della tessera in base alla riga ed alla colonna
	 * su cui è situata
	 */
	inline unsigned getProfondita(){ return riga%2 == 0 ? (colonna%2==0 ? 1 : 2) : (colonna%2==0 ? 3 : 4); }

	/*
	 * Operatore == per vedere se due tessere sono rimovibili tra loro
	 * @param t, tessera da comparare
	 */
	bool operator==(const Tessera &t){
		if(t.id == id) return true;
		if(t.tipo == FIORI && tipo == FIORI) return true;
		if(t.tipo == STAGIONI && tipo == STAGIONI) return true;
		return false;
	}


	/*
	 * Setter e Getter
	 */
	bool isCancellata() const { return cancellata; }

	unsigned getColonna() const { return colonna; }

	void setColonna(unsigned colonna) {
		this->colonna = colonna;
		setX(GlobalValues::getMatrixX() + colonna*(GlobalValues::getScaledWidthTessera()/2));
	}

	inline unsigned getId() const { return id; }

	unsigned getRiga() const { return riga; }

	void setRiga(unsigned riga) {
		this->riga = riga;
		setY(GlobalValues::getMatrixY() + (riga*GlobalValues::getScaledHeightTessera()/2));
	}

	inline TIPOLOGIA getTipo() const { return tipo; }

	void setId(unsigned id) {
		this->id = id;
		this->path = "t" + to_string(id) + ".png";
	}
};


#endif /* TESSERA_H_ */
