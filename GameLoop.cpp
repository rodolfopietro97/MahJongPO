/*
 * GameLoop.cpp
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Implementazione del GameLoop
 */
#include "GameLoop.h"

bool init() {
	al_init_font_addon();
	al_init_ttf_addon();
	return al_init() && al_init_image_addon() && al_install_mouse();
}

void loop() {
	/*
	 *	Inizializzazione componenti
	 */
	// Finestra principale
	Window finestraDiGioco;
	// Gestore eventi
	Event gestoreEventi(finestraDiGioco.getDisplay());
	// Disegnatore a cui passo l' immagine da disegnare quando si passa con il mouse su un oggetto (evento hover)
	Image hover(finestraDiGioco.getDisplay(), "hover.png", 10, 10, 0, 0, 0, 0);
	Drawer disegnatore(hover);

	// elementi schermata iniziale
	vector<Image> bottoniSchermataIniziale;
	bottoniSchermataIniziale.push_back(Image(finestraDiGioco.getDisplay(), "button.png", 500, 100, GlobalValues::getWindowWidth(), 100, 0, 150));
	bottoniSchermataIniziale.push_back(Image(finestraDiGioco.getDisplay(), "button.png", 500, 100, GlobalValues::getWindowWidth(), 100, 0, 270));
	bottoniSchermataIniziale.push_back(Image(finestraDiGioco.getDisplay(), "buttonExit.png", 500, 100, GlobalValues::getWindowWidth(), 100, 0, 390));
	// bottone per decidere il layout del livello
	bottoniSchermataIniziale.push_back(Image(finestraDiGioco.getDisplay(), "button.png", 500, 100, GlobalValues::getWindowWidth()/2-1, 100, 0, 540));
	bottoniSchermataIniziale.push_back(Image(finestraDiGioco.getDisplay(), "button.png", 500, 100, GlobalValues::getWindowWidth()/2-1, 100, GlobalValues::getWindowWidth()/2 +1, 540));

	list<Text> testiSchermataIniziale;
	testiSchermataIniziale.push_back(Text("tempsitc.ttf", 70, "MahJongPO", Colors::BLACK, GlobalValues::getWindowWidth()/2, 15, true));
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 50, "Play", Colors::BLACK, GlobalValues::getWindowWidth()/2, 175, true));
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 50, "Info", Colors::BLACK, GlobalValues::getWindowWidth()/2, 295, true));
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 50, "Exit", Colors::BLACK, GlobalValues::getWindowWidth()/2, 415, true));
	// testi dei bottoni per decidere il layout del livello
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 30, "Layout Tavolo Di Gioco:", Colors::BLACK, GlobalValues::getWindowWidth()/2, 500, true));
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 50, "Semplice", Colors::BLACK, GlobalValues::getWindowWidth()/4, 565, true));
	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 50, "Tartarugha", Colors::BLACK, GlobalValues::getWindowWidth()/2 + GlobalValues::getWindowWidth()/4, 565, true));

	testiSchermataIniziale.push_back(Text("Allura-Regular.otf", 20, "Creato da: Rodolfo Pietro Calabro' e Ippolito Bruno", Colors::BLACK, GlobalValues::getWindowWidth()/2, GlobalValues::getWindowHeight()-20, true));

	// Elementi schermata informazioni
	Image logo(finestraDiGioco.getDisplay(), "icona.png", 500, 500, GlobalValues::getWindowWidth()/2, GlobalValues::getWindowHeight()/2, GlobalValues::getWindowWidth()/4, GlobalValues::getWindowHeight()/4);
	list<Text> testiSchermataInformazioni;
	testiSchermataInformazioni.push_back(Text("Allura-Regular.otf", 35, "Informazioni su MahJongPO", Colors::BLACK, GlobalValues::getWindowWidth()/2, 0, true));
	testiSchermataInformazioni.push_back(Text("Allura-Regular.otf", 20, "Gioco del MahJong realizzato in c++ con Allegro5,", Colors::BLACK, GlobalValues::getWindowWidth()/2, 50, true));
	testiSchermataInformazioni.push_back(Text("Allura-Regular.otf", 20, "Per il progetto di 'Programmazione Ad Ogetti' del C.D.L", Colors::BLACK, GlobalValues::getWindowWidth()/2, 70, true));
	testiSchermataInformazioni.push_back(Text("Allura-Regular.otf", 20, "in Informatica @unical.", Colors::BLACK, GlobalValues::getWindowWidth()/2, 90, true));

	// Elementi schermata di gioco
	Text report("Allura-Regular.otf", 20, "Punteggio: " + to_string(GlobalValues::getScore()), Colors::BLACK, 5, 5, false);
	Image tavoloDiGioco(finestraDiGioco.getDisplay(), "tavoloDiGioco.png", 1200, 720, GlobalValues::getMatrixWidth(), GlobalValues::getMatrixHeight(), GlobalValues::getMatrixX(), GlobalValues::getMatrixY());
	Image bottoneIndizio(finestraDiGioco.getDisplay(), "buttonIndietro.png", 500, 50, GlobalValues::getWindowWidth()/4, 50, GlobalValues::getWindowWidth()-(GlobalValues::getWindowWidth()/4), 0);
	Text indizioText("Allura-Regular.otf", 30, "Indizio", Colors::BLACK, GlobalValues::getWindowWidth()-(GlobalValues::getWindowWidth()/8), 5, true);

	//TARTARUGHA
	unsigned tavoloTartarugha[18][30]= {
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0  },
		{ 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0  },
		{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  }
	};

	// LIVELLO SEMPLICE
	unsigned tavoloSemplice[18][30]= {
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		{ 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0  },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  }
	};


	Livello l(finestraDiGioco.getDisplay(), tavoloSemplice);


	/*
	 * in fase di debug, serve per vedere se nella matrice ci sono esattamente 168 carte (4 cart per tipo)
	 */
	// unsigned count=0;
	// for(unsigned i=0; i<GlobalValues::getRighe(); i++)
	// 	for(unsigned j=0; j<GlobalValues::getColonne(); j++)
	// 		if(tavoloSemplice[i][j]==1) count++;
	// cout << count;

	// bottone indietro comune alla schermata informazioni e play
	Image bottoneIndietro(finestraDiGioco.getDisplay(), "buttonIndietroExit.png", 500, 50, GlobalValues::getWindowWidth(), 50, 0, GlobalValues::getWindowHeight()-50);
	Text indietroText("Allura-Regular.otf", 50, "Indietro", Colors::BLACK, GlobalValues::getWindowWidth()/2, GlobalValues::getWindowHeight()-50, true);

	/*
	 * Loop Principale
	 */
	while (!GlobalValues::isGameStop()) {
		/*
		 * Eventi
		 */
		if(gestoreEventi.onGameClose()) GlobalValues::stopGame();
		switch (GlobalValues::getCurrentScreen()) {
			case INITIAL:
				// clicco sul bottone play
				gestoreEventi.click(&bottoniSchermataIniziale[0]) ? GlobalValues::setCurrentScreen(PLAY) : GlobalValues::setCurrentScreen(GlobalValues::getCurrentScreen());
				// clicco sul bottone info
				gestoreEventi.click(&bottoniSchermataIniziale[1]) ? GlobalValues::setCurrentScreen(ABOUT) : GlobalValues::setCurrentScreen(GlobalValues::getCurrentScreen());
				// clicco sul bottone exit
				gestoreEventi.click(&bottoniSchermataIniziale[2]) ? GlobalValues::stopGame() : GlobalValues::setCurrentScreen(GlobalValues::getCurrentScreen());
				// clicco sul bottone del layout di livello semplice
				if(gestoreEventi.click(&bottoniSchermataIniziale[3])){
					l.inizializzaTavoloDiGioco(tavoloSemplice);
					l.resetGame();
					al_show_native_message_box(
						 finestraDiGioco.getDisplay(),
						 "Cambiamento Layout Tessere",
						 "Layout \"Semplice\" impostato",
						 "Clicca \"ok\" per continuare",
						 NULL,
						 ALLEGRO_MESSAGEBOX_QUESTION
					);
				}
				// clicco sul bottone del layout di tartarugha
				if(gestoreEventi.click(&bottoniSchermataIniziale[4])){
					l.inizializzaTavoloDiGioco(tavoloTartarugha);
					l.resetGame();
					al_show_native_message_box(
						 finestraDiGioco.getDisplay(),
						 "Cambiamento Layout Tessere",
						 "Layout \"Tartarugha\" impostato",
						 "Clicca \"ok\" per continuare",
						 NULL,
						 ALLEGRO_MESSAGEBOX_QUESTION
					);
				}
				break;

			case ABOUT:
				// clicco sul bottone indietro (non metto funziioni perchè tanto è solo una riga di codice)
				gestoreEventi.click(&bottoneIndietro) ? GlobalValues::setCurrentScreen(INITIAL) : GlobalValues::setCurrentScreen(GlobalValues::getCurrentScreen());
				break;

			case PLAY:
				// clicco sul bottone indietro
				if(gestoreEventi.click(&bottoneIndietro)){
		            int scelta = al_show_native_message_box(
		               finestraDiGioco.getDisplay(),
		               "Uscita",
		               "Sei sicuro di voler terminare?",
		               "Se clicchi \"ok\""
		               " perderai la partita",
		               NULL,
		               ALLEGRO_MESSAGEBOX_OK_CANCEL
		            );

		            if(scelta == 1){
									l.resetGame();
		                GlobalValues::setCurrentScreen(INITIAL);
		            }
				}

				// eventi associati al livello di gioco
				l.listenEvents(gestoreEventi);

				// se clicco l' indizio
				if(gestoreEventi.click(&bottoneIndizio)) GlobalValues::showIndizio();

				// aggiorna i punteggi
				report.setText("Punteggio: " + to_string(GlobalValues::getScore()));
				break;

			default:
				break;
		}

		/*
		 * Disegno
		 */
		switch (GlobalValues::getCurrentScreen()) {
			case INITIAL:
				// Disegno i bottoni della schermataa iniziale
				for(auto &i : bottoniSchermataIniziale) gestoreEventi.hover(&i) ? disegnatore.drawImageHover(i) : disegnatore.drawImage(i);
				// Disegno i testi della schermata iniziale
				for(auto i : testiSchermataIniziale) disegnatore.drawText(i);
				break;

			case ABOUT:
				// disegno i testi della schermata iniziale
				for(auto i : testiSchermataInformazioni) disegnatore.drawText(i);

				// disegno il logo
				disegnatore.drawImage(logo);

				// Disegno il bottone indietro
				gestoreEventi.hover(&bottoneIndietro) ? disegnatore.drawImageHover(bottoneIndietro) : disegnatore.drawImage(bottoneIndietro);
				disegnatore.drawText(indietroText);
				break;

			case PLAY:
				// Disegno il report (ci dirà punteggio e tutto)
				disegnatore.drawText(report);

				// Disegno il bottone degli indizi
				gestoreEventi.hover(&bottoneIndizio) ? disegnatore.drawImageHover(bottoneIndizio) : disegnatore.drawImage(bottoneIndizio);
				disegnatore.drawText(indizioText);

				// Disegno il tavolo di gioco
				if(GlobalValues::isTavoloDiGioco()) disegnatore.drawImage(tavoloDiGioco);

				// Disegno il bottone indietro
				gestoreEventi.hover(&bottoneIndietro) ? disegnatore.drawImageHover(bottoneIndietro) : disegnatore.drawImage(bottoneIndietro);
				disegnatore.drawText(indietroText);

				l.draw(disegnatore);
				break;

			default:
				GlobalValues::setCurrentScreen(INITIAL);
				break;
		}


		/*
		 * Aggiornamento
		 */
		finestraDiGioco.flip();
		finestraDiGioco.refresh();
		finestraDiGioco.sleep(0.05);
	}
}

void exit() {
	GlobalValues::stopGame();
}
