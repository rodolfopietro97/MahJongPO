/*
 * Mazzo.h
 *
 *  Created on: 27 apr 2018
 *      Author: rodolfo
 *
 *  Classe che rappresenta un mazzo di carte (Ovvero un insieme di carte)
 */

#ifndef MAZZO_H_
#define MAZZO_H_

#include "Tessera.h"
#include <vector>


using namespace std;

class Mazzo : public vector<Tessera> {

public:
	/*
	 * Costruttore di defaul che crea il mazzo
	 * @param display della finestra corrente
	 */
	Mazzo(ALLEGRO_DISPLAY *display){
		// inizializzo tutte le tessere del mahjong
		for (unsigned i = 1; i < 43; i++) {
			if (i>=1 && i<=9) push_back(Tessera(display, i, 0, 0, CERCHI)); // pusho i cerchi
			else if (i>=10 && i <= 18) push_back(Tessera(display, i, 0, 0, CARATTERI)); // pusho i caratteri
			else if (i>=19 && i<=27) push_back(Tessera(display, i, 0, 0, BAMBU)); // pusho i bambù
			else if (i>=28 && i<=31) push_back(Tessera(display, i, 0, 0, VENTI)); // pusho i venti
			else if (i>=32 && i<=35) push_back(Tessera(display, i, 0, 0, FIORI)); // pusho i fiori
			else if (i>=36 && i<=38) push_back(Tessera(display, i, 0, 0, DRAGHI)); // pusho i draghi
			else if (i>=39 && i<=42) push_back(Tessera(display, i, 0, 0, STAGIONI)); // pusho le stagioni
		}
	}

	/*
	 * Restituisce una copia del mazzo di carte.
	 * Utile perchè così dichiaro sempre un mazzo solo e ne restituisco sempre uan copia quando serve
	 */
	vector<Tessera> getMazzo(){
		return *this;
	}
};


#endif /* MAZZO_H_ */
