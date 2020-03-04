/*
 * MahJongMain.cpp
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Main del gioco
 */
#include "GameLoop.h"

/*
 * Per avere l' assetPath corretta
 */
#include <stdio.h>  /* per FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS // se sono in windows
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else // altrimenti
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
string getCurrentWorkingDir(); // restituisce la corrente directory di lavoro (per gli sprites)


/*
 * Inizializzazione dei contenuti globali
 * (Passo molto importante da fare ad inizio gioco)
 */
screenType GlobalValues::currentScreen = INITIAL;

bool GlobalValues::gameStop = false;

float GlobalValues::windowWidth = 800;
float GlobalValues::windowHeight = 700;
Color GlobalValues::windowColor = Color(40, 255, 148, 255);
string GlobalValues::windowTitle = "MahJong PO";

string GlobalValues::assetPath = getCurrentWorkingDir() + "/assets/";

float GlobalValues::originalWidthTessera = 60;
float GlobalValues::originalHeightTessera = 75;

/*
 * Punteggio
 */
unsigned GlobalValues::score = 0;

/*
 * Se settata a true, disegna il tavolo di background delle tessere (Mi seviva per vedere se le tessere venivano posizionate bene e per i vari test..)
 * @see { Utile in fase di debbugging.}
 */
bool GlobalValues::tavoloDiGioco = false;

/*
 * @see { Per capire tutti questi settaggi guarda il file "assets/settaggiGrafica.jpg" }
 */
unsigned GlobalValues::righe = 18;
unsigned GlobalValues::colonne = 30;

float GlobalValues::spaceX = 50;
float GlobalValues::spaceY = 50;

float GlobalValues::matrixX = GlobalValues::getSpaceX();
float GlobalValues::matrixY = 30 + GlobalValues::getSpaceY();

float GlobalValues::matrixWidth = GlobalValues::getWindowWidth() - (2*GlobalValues::getSpaceX());
float GlobalValues::matrixHeight = GlobalValues::getWindowHeight() - 50 - 30 - (2*GlobalValues::getSpaceY());

float GlobalValues::scaledWidthTessera = (GlobalValues::getMatrixWidth()) / (GlobalValues::getColonne()/2);
float GlobalValues::scaledHeightTessera = (GlobalValues::getMatrixHeight()) / (GlobalValues::getRighe()/2);

/*
 * per questioni di semplicità la variabile che ci da un indizio durante la partita
 * è stata messa nelle GlobalValues. Così facendo inizialmente (come ovvio che sia)
 * NON sono attivati gli indizi, quando poi durrante il gioco si cliccherà su indizio,
 * tale variabile verà abilitata o meno.
 * @see { Lasciala a false }
 */
bool GlobalValues::indizio = false;

int main() {

  /*
   * Procedura automatica che setta la risoluzione della finestra.
   * In caso ci fossero problei, le dimensioni sono date dalle GlobalValues
   */
  ALLEGRO_MONITOR_INFO info;
  if(al_get_monitor_info(ALLEGRO_DEFAULT_DISPLAY_ADAPTER, &info)){
    int w = info.x2 - info.x1;
    int h = info.y2 - info.y1;
    GlobalValues::setWindowWidth((float)w/2);
    GlobalValues::setWindowHeight((float)h/2);
  }

  /*
   * Inizio del game loop del gioco
   */
	init() ? loop() : exit();
	return 0;
}

string getCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  string current_working_dir(buff);
  return current_working_dir;
}
