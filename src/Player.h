/*
 * Player.h
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#ifndef PLAYER_H_
#define PLAYER_H_

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

#include "Hand.h"
#include "Deck.h"

using namespace std;
using namespace cv;


class Player {
public:
	Player(int id);
	virtual ~Player();

	int playHand(Mat communityCards, vector<float> bets, int betsLeft);

	int id;
	void showHandMat();
	void printHand(Deck &deck);

	void printBestHand(Deck &deck);
	void showBestHandMat();

	void clearHand();

	Mat startingHandProbability;
	Mat stayingInProbability;
	Mat iWinProbability;

	void drawCard(Point card); // add a card to hand
	void showCards(); // print out cards

	void makeBestHand(Mat communityCards);
	Hand bestHand;
	Hand myHand;


};

#endif /* PLAYER_H_ */
