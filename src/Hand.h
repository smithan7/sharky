/*
 * Hand.h
 *
 *  Created on: Oct 9, 2016
 *      Author: andy
 */

#ifndef HAND_H_
#define HAND_H_


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

#include "Deck.h";

using namespace std;
using namespace cv;

class Hand {
public:
	Hand();
	virtual ~Hand();

	void cardIn( Point card );
	Mat hand;

	void clearHand();

	string name;
	int rank;
	vector<int> rankValues;

	Hand makeBestHand();
	int checkForRuns();
	int checkForFlush();
	void checkForMatchingSets(  int &pair1, int &pair2, int &trips, int &quads  );
	Point searchMatForKicker( Mat &mat );

	bool checkForStraightFlush( int run, int flush, Hand &bestHand);
	Hand get4ofAKind( int quads );
	Hand getFullHouse( int trips, int pair1);
	Hand getFlush( int suit );
	Hand getStraight( int run );
	Hand get3ofAKind( int trips );
	Hand get2Pairs( int pair1, int pair2 );
	Hand get2ofAKind( int pair1 );
	Hand getHighCard();

	void printHand(Deck &deck);
	void showHandMat(string name);
};

#endif /* HAND_H_ */
