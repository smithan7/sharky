/*
 * table.h
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include "Deck.h"
#include "Player.h"

using namespace std;
using namespace cv;

class Table {
public:
	Table(int nPlayers);
	int nPlayers;
	virtual ~Table();

	void newHand();
	Deck deck;
	vector<Player> players;

	void dealSpecificCard( int player, string suit, string value );
	void dealHoleCards();
	void dealFlop();
	void drawCard(Point in); // add a card to hand
	void showCommunityCards(); // print out cards

	void showHands();
	void showBestHands();

	void makePlayerHands();
	vector<int> getWinningHand();

	Mat communityCards;
	int totalPot;
	int bet;

};

#endif /* TABLE_H_ */
