/*
 * GlobalValues.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 * Classe contenente tutti i dati globali del gioco
 */

#ifndef GLOBALVALUES_H_
#define GLOBALVALUES_H_

#include <string>
using namespace std;

#include "Color.h"

/*
 * Tipo di schermataa di gioco
 */
enum screenType {
	INITIAL = 0, // schermo iniziale
	ABOUT, // schermo delle impostazioni
	PLAY 	// schermata di gioco
};

class GlobalValues {

private:
	/*
	 * Schermata di gioco corrente
	 */
	static screenType currentScreen;

	/*
	 * Path contenente gli asset
	 */
	static string assetPath;

	/*
	 * Colore della finestra
	 */
	static Color windowColor;
	/*
	 * Titolo della finestra
	 */
	static string windowTitle;



	/*
	 * Ci dice se il gioco è stato stoppato o meno
	 */
	static bool gameStop;

	/*
	 * Paramettri per la grafica:
	 *
	 * della finestra,
	 * del tavolo di gioco
	 * e delle tessere
	 */

	/*
	 * Dimensioni della finestra di gioco
	 */
	static float windowWidth, windowHeight;

	/*
	 * Spazi tra la finestra ed il tavolo di gioco
	 */
	static float spaceX, spaceY;

	/*
	 * Cordinate della matrice di gioco
	 */
	static float matrixX, matrixY;

	/*
	 * Dimensioni della matrice di gioco
	 */
	static float matrixWidth, matrixHeight;

	/*
	 * Numero di righe e colonne della matrice di gioco
	 */
	static unsigned righe, colonne;

	/*
	 * Dimensioni ORIGINALI delle tessere di gioco
	 */
	static float originalWidthTessera, originalHeightTessera;

	/*
	 * Dimensioni SCALATE delle tessere di gioco (serviranno poi per il disegno nella matrice)
	 */
	static float scaledWidthTessera, scaledHeightTessera;

	/*
	 * Indizio di gioco
	 */
	static bool indizio;

	/*
	 * Punteggio
	 */
	static unsigned score;

	/*
	 * Ci dice se vogliamo disegnare o meno il tavolo di gioco
	 */
	static bool tavoloDiGioco;

public:
	/*
	 * Setter e getter
	 */


	static const string& getAssetPath() {
		return assetPath;
	}

	static screenType getCurrentScreen() {
		return currentScreen;
	}

	static void setCurrentScreen(screenType curr) {
		currentScreen = curr;
	}

	static bool isGameStop() {
		return gameStop;
	}

	static void stopGame() {
		gameStop = true;
	}

	static float getOriginalHeightTessera() {
		return originalHeightTessera;
	}

	static float getOriginalWidthTessera() {
		return originalWidthTessera;
	}

	static float getScaledHeightTessera() {
		return scaledHeightTessera;
	}

	static void setScaledHeightTessera(float h) {
		scaledHeightTessera = h;
	}

	static float getScaledWidthTessera() {
		return scaledWidthTessera;
	}

	static void setScaledWidthTessera(float w) {
		scaledWidthTessera = w;
	}

	/*
	 * @see { Unicamente per l' inizio del gioco! }
	 */
	static void setWindowWidth(float w) {
		windowWidth = w;
	}
	static void setWindowHeight(float h) {
		windowHeight = h;
	}


	static float getWindowHeight() {
		return windowHeight;
	}

	static float getWindowWidth() {
		return windowWidth;
	}

	static Color getWindowColor() {
		return windowColor;
	}

	static const string& getWindowTitle() {
		return windowTitle;
	}

	static unsigned getColonne() {
		return colonne;
	}

	static float getMatrixX() {
		return matrixX;
	}

	static float getMatrixY() {
		return matrixY;
	}

	static unsigned getRighe() {
		return righe;
	}

	static float getSpaceX() {
		return spaceX;
	}

	static float getSpaceY() {
		return spaceY;
	}

	static float getMatrixHeight() {
		return matrixHeight;
	}

	static float getMatrixWidth() {
		return matrixWidth;
	}

	static bool isIndizio() {
		return indizio;
	}

	static void showIndizio() {
		indizio = true;
	}

	static void hideIndizio() {
		indizio = false;
	}

	static unsigned getScore() {
		return score;
	}

	static void setScore(unsigned s) {
		score = s;
	}

	static bool isTavoloDiGioco() {
		return tavoloDiGioco;
	}
};

#endif /* GLOBALVALUES_H_ */
