/*
 * Livello.h
 *
 *  Created on: 27 apr 2018
 *      Author: rodolfo
 *
 *  Livello di gioco
 */

#ifndef LIVELLO_H_
#define LIVELLO_H_

#include "Mazzo.h"
#include "Drawer.h"
#include "Event.h"
#include "GlobalValues.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
using namespace std;

/*
 * Costanti per facilitare la lettura e l' eventuale modifica del codice
 */
const unsigned int righe = GlobalValues::getRighe();
const unsigned int colonne = GlobalValues::getColonne();

class Livello {

private:
	/*
	 * Mazzo che verrà utilizzato e le cui tessere verranno posizionate in base
	 * as una matrice tavolo
	 */
	vector<Tessera> mazzo;

	/*
	 * Display della finestra corrente
	 */
	ALLEGRO_DISPLAY *display;

	/*
	 * Matrice del tavolo di gioco
	 */
	unsigned matriceTavolo[18][30];

	/*
	 * Matrice contenente gli indici. Serve per collegare l' indice del vettore con la posizione (riga,colonna) della tessera
	 */
	int indici[18][30] = { 0 };

	/*
	 * Indice della carta cliccata
	 */
	int indiceCliccata;

	/*
	 * Ci da gli indici delle prime tessere he riesce ad indiziare
	 */
	int indiceIndiziata1 = 0, indiceIndiziata2 = 0;


public:
	/*
	 * Costruttore Parametrizzato
	 * @param display di gioco della finestra corrente
	 * @param tavolo di gioco
	 */
	Livello(ALLEGRO_DISPLAY *display, unsigned tavolo[18][30]) : display(display) {
		/*
		 * inizializzo il mazzo di gioco
		 */
		mazzo.clear();
		indiceCliccata = -1;

		/*
		 * inizializzo il tavolo
		 */
		inizializzaTavoloDiGioco(tavolo);

		/*
		 * posiziono le carte nel mazzo in base alla matriceTavolo
		 */
		inizializzaMazzo(mazzo);
	}

	void inizializzaTavoloDiGioco(unsigned tavolo[18][30]){
		for(unsigned i=0; i<righe; i++)
			for(unsigned j=0; j<colonne; j++)
				matriceTavolo[i][j] = tavolo[i][j];
	}

	/*
	 * Inizilizza un mazzo di carte in base alla matrice di gioco
	 * @param mazzo da inizializzare
	 */
	void inizializzaMazzo(vector<Tessera> &mazzo){
		// creo un creatore di mazzi di carte (un mazoz ha 42 carte ed è standard)
		Mazzo creatoreMazzo(display);

		/*
		 *  nel mazzo ne inserisco 4 mazzi temporanei uno alla volta (inserisco e mescolo in totale 42*4=166 tessere)
		 *  @see { ricorda che se vuoi inserire una matrice di gioco nuova DEVI mettere esattamente 166 uni, ne più ne meno}
		 */
		srand(time(0));
		auto mazzoTemporaneo = creatoreMazzo.getMazzo();
		random_shuffle(mazzoTemporaneo.begin(),mazzoTemporaneo.end());
		mazzo.insert(mazzo.begin(), mazzoTemporaneo.begin(), mazzoTemporaneo.end());
		random_shuffle(mazzoTemporaneo.begin(),mazzoTemporaneo.end());
		mazzo.insert(mazzo.end(), mazzoTemporaneo.begin(), mazzoTemporaneo.end());
		random_shuffle(mazzoTemporaneo.begin(),mazzoTemporaneo.end());
		mazzo.insert(mazzo.end(), mazzoTemporaneo.begin(), mazzoTemporaneo.end());
		random_shuffle(mazzoTemporaneo.begin(),mazzoTemporaneo.end());
		mazzo.insert(mazzo.end(), mazzoTemporaneo.begin(), mazzoTemporaneo.end());
		random_shuffle(mazzo.begin(), mazzo.end()); // rimescolo ulteriolmente

		/*
		 * in fase di debug, serve per vedere se nella matrice ci sono esattamente 168 carte (4 cart per tipo)
		 */
//cout << endl << mazzo.size() << endl;

		unsigned index=0;
		for (unsigned i = 0; i < righe; i++) {
			for (unsigned j = 0; j < colonne; j++) {
				indici[i][j] = -1;
				if(matriceTavolo[i][j] == 1 && index < mazzo.size()){
					mazzo[index].setRiga(i);
					mazzo[index].setColonna(j);
					indici[i][j] = index;
					index++;
				}
			}
		}


	}

	/*
	 * Disegna il mazzo di tessere per livelli di profondità delle tessere stesse
	 */
	void draw(Drawer &disegnatore){
		// tessere di livello 1
		for(auto &i : mazzo) if(i.getProfondita() == 1)disegnatore.drawTessera(i);
		// tessere di livello 2
		for(auto &i : mazzo) if(i.getProfondita() == 2)disegnatore.drawTessera(i);
		// tessere di livello 3
		for(auto &i : mazzo) if(i.getProfondita() == 3)disegnatore.drawTessera(i);
		// tessere di livello 4
		for(auto &i : mazzo) if(i.getProfondita() == 4)disegnatore.drawTessera(i);

		// disegna l' eventuale carta cliccata dal mouse
		if(indiceCliccata != -1) disegnatore.drawTesseraHover(mazzo[indiceCliccata]);

		// se è stato cliccato l' indizio
		if(GlobalValues::isIndizio()){
			disegnatore.drawTesseraHover(mazzo[indiceIndiziata1]);
			disegnatore.drawTesseraHover(mazzo[indiceIndiziata2]);
			// fa si che quando clicco l' indizio si sclicca la carta eventualmente cliccata
			if(indiceCliccata!=-1) indiceCliccata = -1;
			//al_rest(0.5);
			//GlobalValues::hideIndizio();
		}
	}

	void listenEvents(Event &gestoreEventi){
		/*
		 * Gestione dei click delle tessere
		 */
		for(unsigned i=0; i< mazzo.size(); i++){
			// se non ho cliccato alcuna carta
			if(indiceCliccata==-1){
				if(gestoreEventi.click(&mazzo[i]) && !haTessereSopra(i) && haAlmenoUnLatoLibero(i)){
					al_rest(0.1);
					indiceCliccata = i;
					GlobalValues::hideIndizio();
				}
			}
			// se ho cliccato in precedenza qualche carta
			else{
				if(gestoreEventi.click(&mazzo[i]) && !haTessereSopra(i) && haAlmenoUnLatoLibero(i)){
					al_rest(0.1);
					// se posso riuovere le due tessere
					if(rimovibili(i, indiceCliccata)){
						mazzo[i].cancellaTessera();
						mazzo[indiceCliccata].cancellaTessera();
						indiceCliccata=-1;

						// se si rimuovono due carte con un indizio gli indizi devono finire, o si bara!!
						if (GlobalValues::isIndizio()) GlobalValues::hideIndizio();

						// aggiorno il punteggio
						GlobalValues::setScore(GlobalValues::getScore()+2);
					}
					// se non posso rimuovere le due tessere
					else indiceCliccata=-1;
				}
			}
		}

		/*
		 * Vede se la partita è finita o meno
		 */
		// se ho vinto
		if (vinto()) {
			int scelta = al_show_native_message_box(
					display,
					"Vittoria!",
					"Congratulazioni hai vinto la partita!", "Clicca \"ok\""
							" per terminare.",
					NULL, ALLEGRO_MESSAGEBOX_WARN);

			if (scelta == 1) {
				resetGame();
				GlobalValues::setCurrentScreen(INITIAL);
			}
		}
		else { // L' else è necessario perchè se sei nel caso di vittoria se ne vanno anche tutte le mosse e di conseguenza  significherebbe che hai anche perso!
			// se ho perso
			if (perso()) {
				int scelta = al_show_native_message_box(
						display,
						"Sconfitta!",
						"Non puoi fare più mosse hai perso la partita :(", "Clicca \"ok\""
								" per terminare.",
						NULL, ALLEGRO_MESSAGEBOX_WARN);

				if (scelta == 1) {
					resetGame();
					GlobalValues::setCurrentScreen(INITIAL);
				}
			}
		}

		/*
		 * verifica le carte da indiziare
		 */
		for(unsigned i=0; i<mazzo.size() && GlobalValues::isIndizio(); i++){
			for(unsigned j=0; j<mazzo.size() && GlobalValues::isIndizio(); j++){
				if(rimovibili(i, j)) {
					indiceIndiziata1 = i;
					indiceIndiziata2 = j;
					break;
				}
			}
		}

	}

	/*
	 * Ci dice se due tessere che si trovano agli indici i1, i2 sono rimovibili
	 */
	bool rimovibili(int i1, int i2){
		return mazzo[i1] == mazzo[i2] // se sono lo stesso tipo di tessera
		&& i1 != i2 // Questo serve per evitare l' autorimozione se per esempio tengo premuso su uan tessera!
		&& !haTessereSopra(i1)
		&& !haTessereSopra(i2)
		&& haAlmenoUnLatoLibero(i1)
		&& haAlmenoUnLatoLibero(i2)
		&& !mazzo[i1].isCancellata() // ovvia ma serve per il controllo delle perdite
		&& !mazzo[i2].isCancellata(); // ovvia ma serve per il controllo delle perdite
	}

	/*
	 * Funzione ciclica che ci dice se abbiamo vinto!.
	 * La partita è vinta se e solo se tutte le tessere sono cancellate.
	 * @return vinto o no
	 */
	bool vinto(){
		for(auto &i : mazzo) if(i.isCancellata() == false) return false;
		return true;
	}

	/*
	 * Ci dice se la cartaa a tessee a sinistra
	 * @param i, indice della tessera nel mazzo
	 */
	bool haTessereSopra(int i){
		unsigned r = mazzo[i].getRiga(),
				 c = mazzo[i].getColonna();
		// se il livello di profondità della tessera nel mazzo alla posizione indice è 4
		if(mazzo[i].getProfondita() == 4) return false;

		// se il livello di profondità della tessera nel mazzo alla posizione indice è 3
		else if(mazzo[i].getProfondita() == 3)
			return presente(r, c-1) || presente(r, c+1); // coperta dal livello 4

		// se il livello di profondità della tessera nel mazzo alla posizione indice è 2
		else if(mazzo[i].getProfondita() == 2)
			return presente(r-1,c) || presente(r+1, c) || presente(r+1, c+1) // coperta dal livello 4
					||
				   presente(r-1, c-1) || presente(r+1, c-1) || presente(r-1, c+1); // coperte dal livello 3

		// se il livello di profondità della tessera nel mazzo alla posizione indice è 1
		return presente(r-1,c-1) || presente(r+1,c-1) || presente(r+1,c+1) // coperte dal livello 4
				    ||
				   presente(r-1,c) || presente(r+1,c) // coperte dal livello 3
					||
				   presente(r, c-1) || presente(r,c+1); // coperte dal livello 2
	}

	/*
	 * ci dice se sono presenti tessere sulla matrice nella posizione (i,j)
	 * @param i, riga su cui verificare la presenz della tessera
	 * @param j, colonna su cui verificare la presenza della tessera
	 * @return true  : se la tessera è presente sulla matrice nell posizione (i;j)
	 * 		   false : altrimenti
	 */
	bool presente(int i, int j){
		if(i >= 0 && i < righe && j >= 0 && j < colonne){
			if(matriceTavolo[i][j] == 0) return false;
			else{
				if(mazzo[indici[i][j]].isCancellata()) return false;
				else return true;
			}
		}
		return false;
	}


	/*
	 * Ci dice se la tessera ha almeno un lato libero
	 * @param i, indice della tessera nel mazzo
	 */
	bool haAlmenoUnLatoLibero(int i){
		 // Collonna sinistra (guardo solo il lato destro)
		 if(mazzo[i].getColonna() <= 2) //return !presente(mazzo[i].getRiga(), mazzo[i].getColonna()+2);
			 return true;
		 // Colonna destra (guardo solo il lato sinistro)
		 if(mazzo[i].getColonna() >= colonne-2) //return !presente(mazzo[i].getRiga(), mazzo[i].getColonna()-2);
			 return true;
		 // Parte centrale (guardo entrambi i lati)
		 return !presente(mazzo[i].getRiga(), mazzo[i].getColonna()+2) || !presente(mazzo[i].getRiga(), mazzo[i].getColonna()-2);
	}
	/*
	 * Funzione che ci dice se abbiamo perso :(
	 * Una partita è persa quando non ci possono fare più mosse,
	 * ovvero se non ci sono più tessere rimovibili
	 * @return perso o no
	 *
	 */
	bool perso(){
		for(unsigned i=0; i<mazzo.size(); i++){
			for(unsigned j=0; j<mazzo.size(); j++){
				if(rimovibili(i, j)) return false;

			}
		}
		return true;
	}

	/*
	 * Resetta il gioco
	 */
	void resetGame(){
		GlobalValues::setScore(0);
		mazzo.clear();
		inizializzaMazzo(mazzo);
		indiceCliccata = -1;
	}
};



#endif /* LIVELLO_H_ */
