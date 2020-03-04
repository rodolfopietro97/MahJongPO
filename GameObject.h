/*
 * GameObject.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Definisce un ogetto di gioco generico
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class GameObject {

protected:
	/*
	 * Parametri dell' oggetto
	 */
	float width, height, x, y;

public:

	/*
	 * Costruttore di default
	 */
	GameObject() :
			width(0),
			height(0),
			x(0),
			y(0) {
	}
	/*
	 * Costruttore Parametrizzato
	 * @param width dell' oggetto
	 * @param height dell' oggetto
	 * @param x dell' oggetto
	 * @param y dell' oggetto
	 */
	GameObject(float width, float height, float x, float y) :
			width(width),
			height(height),
			x(x),
			y(y) {
	}
	/*
	 * Setter e Getter
	 */
	inline float getHeight() const {
		return height;
	}
	inline void setHeight(float height) {
		this->height = height;
	}
	inline float getWidth() const {
		return width;
	}
	inline void setWidth(float width) {
		this->width = width;
	}
	inline float getX() const {
		return x;
	}
	inline void setX(float x) {
		this->x = x;
	}
	inline float getY() const {
		return y;
	}
	inline void setY(float y) {
		this->y = y;
	}
};

#endif /* GAMEOBJECT_H_ */
