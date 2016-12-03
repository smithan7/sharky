/*
 * Deck.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#include "Deck.h"

Deck::Deck() {

	cards = Mat::ones(14,4, CV_8UC1)*255;

	suitS[0] = "Clubs";
	suitS[1] = "Hearts";
	suitS[2] = "Diamonds";
	suitS[3] = "Spades";

	valueS[0] = "Ace";
	valueS[1] = "2";
	valueS[2] = "3";
	valueS[3] = "4";
	valueS[4] = "5";
	valueS[5] = "6";
	valueS[6] = "7";
	valueS[7] = "8";
	valueS[8] = "9";
	valueS[9] = "10";
	valueS[10] = "Jack";
	valueS[11] = "Queen";
	valueS[12] = "King";
	valueS[13] = "Ace";

	for(size_t i=0; i<14; i++){
		valueI[i] = i;
	}
	for(size_t i=0; i<4; i++){
		suitI[i] = i;
	}
}

void Deck::newDeck(){
	cards = Mat::ones(14,4, CV_8UC1)*255;
}

void Deck::printCardName(Point c){
	cout << "   " << valueS[c.y] << " of " << suitS[c.x] << endl;
}

Point Deck::drawRandomCard(){

	Point d(rand() % 4, rand() % 13);
	while( cards.at<uchar>(d) == 0){
		d.x = rand() % 4;
		d.y = rand() % 13;
	}

	cards.at<uchar>(d) = 0;
	return d;
}

Point Deck::drawCardByName( string suit, string value ){


	int sI;
	for(int s = 0; s<4; s++){
		if( suit.compare(suitS[s]) == 0 ){
			sI = s;
			break;
		}
	}

	int vI;
	for(int v = 0; v<14; v++){
		if( value.compare(valueS[v]) == 0 ){
			vI = v;
			break;
		}
	}

	Point c(sI, vI);
	cards.at<uchar>(c) = 0;

	if(vI == 0){
		Point c(sI, 13);
		cards.at<uchar>(c) = 0;
	}

	return c;
}

void Deck::showDeck(){

	namedWindow("Deck", WINDOW_NORMAL);
	imshow("Deck", cards);
	waitKey(1);

}

Point Deck::drawSpecificCard(int s, int v){
	// clubs hearts, diamonds, spades
	// A-K
	Point p(s,v);
	if( cards.at<uchar>(p) == 255){
		cards.at<uchar>(p) = 0;
		return p;
	}
	else{
		Point a(-1,-1);
		return a;
	}
}



Deck::~Deck() {
	// TODO Auto-generated destructor stub
}

