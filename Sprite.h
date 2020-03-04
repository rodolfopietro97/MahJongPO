/*
 * Sprite.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Questa classe rappresenta uno Sprite, ossia un oggetto di gioco
 *  che ha una propria path. Uno sprite può essere un' immagine, un bottone, ...
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "GameObject.h"
#include <string>
using namespace std;

class Sprite: public GameObject {

protected:
	/*
	 * Path dello Sprite
	 */
	string path;

public:
	/*
	 * Costruttore di default
	 */
	Sprite() : GameObject() , path("/") {
	}

	/*
	 * Costruttore parametrizzato
	 * @param width dello Sprite
	 * @param height dello Sprite
	 * @param x dello Sprite
	 * @param y dello Sprite
	 * @param path dello Sprite
	 */
	Sprite(float width, float height, float x, float y, string path) :
			GameObject(width, height, x, y),
			path(path) {
	}

	/*
	 * Metodo di disegno virtuale che dovrà essere implementato
	 * successivamente dalle classi che andranno ad ereditare
	 */
	//virtual void draw() = 0;

	/*
	 * Setter e Getter
	 */
	inline const string& getPath() const {
		return path;
	}
	inline void setPath(const string& path) {
		this->path = path;
	}
};

#endif /* SPRITE_H_ */
