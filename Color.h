/*
 * Color.h
 *
 *  Created on: 22 apr 2018
 *      Author: rodolfo
 *
 *  Struttura che rappresenta un colore
 */

#ifndef COLOR_H_
#define COLOR_H_

struct Color{

public:
	/*
	 * Costruttore Parametrizzato
	 * @param red gradazione rossa del colore
	 * @param green gradazione verde del colore
	 * @param blue gradazione blu del colore
	 * @param alpha gradazione di trasparenza del colore
	 */
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
		red(red),
		green(green),
		blue(blue),
		alpha(alpha){

	}

	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};


/*
 Namespace contenente i colori di default principali
 */
namespace Colors {
	static Color TRASPARENT(0, 0, 0, 0); // trasparente
	static Color WHITE(255, 255, 255, 255); // bianco
	static Color BLACK(0, 0, 0, 0); // nero
	static Color RED(255, 0, 0, 255); // rosso
	static Color GREEN(0, 255, 0, 255); // verde
	static Color BLUE(0, 0, 255, 255); // blu
	static Color BACKGROUND(40, 255, 148, 255);
}



#endif /* COLOR_H_ */
