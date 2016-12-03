/*
 * deck.h
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#ifndef DECK_H_
#define DECK_H_

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Deck {
public:
	Deck();
	virtual ~Deck();

	Mat cards;
	void newDeck();

	Point drawRandomCard();
	Point drawSpecificCard(int s, int v);
	Point drawCardByName( string suit, string value );

	void printCardName(Point c);
	void showDeck();

	string suitS[4];
	string valueS[14];

	int suitI[4];
	int valueI[14];
};

#endif /* DECK_H_ */
