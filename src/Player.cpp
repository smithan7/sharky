/*
 * Player.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#include "Player.h"

Player::Player(int id){
	this->id = id;
	this->startingHandProbability = imread("startingHandProbability.jpg",CV_32F);
}


int Player::playHand(Mat communityCards, vector<float> bets, int betsLeft){

	// use neural net to learn call, fold, increase bet


	// if increase bet
		// use second neural net to evaluate how much to increase


}

void Player::drawCard(Point card){
	myHand.cardIn( card );
}

void Player::clearHand(){
	myHand.clearHand();
	bestHand.clearHand();
}

void Player::makeBestHand(Mat communityCards){
	// add community cards to my hand
	bitwise_or(myHand.hand, communityCards, myHand.hand);
	// make best hand from all cards
	bestHand = myHand.makeBestHand();
	bestHand.showHandMat("best hand p");
	myHand.showHandMat("my hand p");
}

void Player::showHandMat(){

	char bu[20];
	sprintf(bu, "Player %d Hand", id);

	namedWindow(bu, WINDOW_NORMAL);
	imshow(bu, myHand.hand);
	waitKey(1);
}

void Player::showBestHandMat(){

	char bu[50];
	sprintf(bu, "Player %d Best Hand", id);

	namedWindow(bu, WINDOW_NORMAL);
	imshow(bu, bestHand.hand);
	waitKey(1);
}


void Player::printHand(Deck &deck){

	cout << "Player " << id << " hand: " << endl;
	myHand.printHand(deck);
}

void Player::printBestHand(Deck &deck){

	cout << "Player " << id << " best hand: " << endl;
	bestHand.printHand(deck);
}
Player::~Player(){}

