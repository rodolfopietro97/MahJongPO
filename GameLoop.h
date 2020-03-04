/*
 * GameLoop.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 * Game loop del gioco che contiene le due funzioni principali di un game loop
 */

#ifndef GAMELOOP_H_
#define GAMELOOP_H_

/*
 * Inclusioni necessarie
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include <iostream>
#include <vector>
#include <list>
using namespace std;

#include "GlobalValues.h"
#include "Color.h"
#include "Event.h"
#include "Window.h"
#include "Image.h"
#include "Text.h"
#include "Drawer.h"
#include "Tessera.h"
#include "Livello.h"

/*
 * Funzioni principali del game loop
 */
/*
 * Funzione che inizializza il gioco
 * (parte d' inizializzazione del game loop)
 */
bool init();

/*
 * Funzione di loop del game loop
 */
void loop();

/*
 * funzione di uscita del gioco
 */
void exit();




#endif /* GAMELOOP_H_ */
