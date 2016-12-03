/*
 * Hand.cpp
 *
 *  Created on: Oct 9, 2016
 *      Author: andy
 */

#include "Hand.h"

int matValueCount(int v, Mat &mat);
int matSuitCount(int s, Mat &mat);
Point getCardWithValue(int v, Mat &mat);
Point getCardWithSuit(int s, Mat &mat);
void matClearNonSuit( int S, Mat &mat);

Hand::Hand() {
	rank  = -1;
	hand = Mat::zeros(14, 4, CV_8UC1);
}

Hand::~Hand() {}

void Hand::cardIn( Point card ){

	hand.at<uchar>(card) = 255;

	if( card.y == 0 ){ // is an ace
		Point p2(card.x, 13); // suit, value
		hand.at<uchar>(p2) = 255;
	}
}

void Hand::clearHand(){

	rank  = -1;
	hand = Mat::zeros(14, 4, CV_8UC1);
	rankValues.clear();

}

Hand Hand::makeBestHand(){

	this->showHandMat("all cards");

	// check for all sets of pairs
	int pair1 = -1;
	int pair2 = -1;
	int trips = -1;
	int quads = -1;
	checkForMatchingSets( pair1, pair2, trips, quads );

	// check for straight
	int run = checkForRuns();

	// check for flush
	int flush = checkForFlush();

	if( run > 0 && flush >= 0){
		Hand bestHand;
		if( checkForStraightFlush(run, flush, bestHand) ){
			return bestHand;
		}
	}

	if(quads > 0){
		return get4ofAKind(quads);
	}
	else if(trips > 0 && pair1 > 0){
		return getFullHouse(trips, pair1 );
	}
	else if( flush >= 0){
		return getFlush(flush);
	}
	else if( run > 0){
		return getStraight( run );
	}
	else if( trips > 0){
		return get3ofAKind( trips );
	}
	else if(pair1 > 0 && pair2 > 0){
		return get2Pairs( pair1, pair2 );
	}
	else if(pair1 > 0){
		return get2ofAKind( pair1 );
	}
	else{
		return getHighCard();
	}
}

bool Hand::checkForStraightFlush( int run, int flush, Hand &bestHand){

	Mat tHand = Mat::zeros(hand.size(), CV_8UC1);

	for(int v=0; v<14; v++){
		Point c(flush, v);
		tHand.at<uchar>(c) = hand.at<uchar>(c);
	}

	for(int v=13; v>4; v--){ // check downwards Ace - 5, no point starting search at 4
		if( matValueCount(v, tHand) > 0){
			if( matValueCount(v-1, tHand) > 0){
				if( matValueCount(v-2, tHand) > 0){
					if( matValueCount(v-3, tHand) > 0){
						if( matValueCount(v-4, tHand) > 0){

							bestHand.rankValues.push_back( v );
							bestHand.name = "Straight Flush";
							bestHand.rank = 8;
							bestHand.hand.at<uchar>(v,flush) = 255;
							bestHand.hand.at<uchar>(v-1,flush) = 255;
							bestHand.hand.at<uchar>(v-2,flush) = 255;
							bestHand.hand.at<uchar>(v-3,flush) = 255;
							bestHand.hand.at<uchar>(v-4,flush) = 255;

							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

Hand Hand::get4ofAKind( int quads ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int s=0; s<4; s++){
		Point q(s,quads);
		bestHand.hand.at<uchar>( q ) = 255;
		tHand.at<uchar>( q ) = 0;
	}

	bestHand.rankValues.push_back(quads); // x=suit, y=value

	Point k = searchMatForKicker( tHand );
	bestHand.hand.at<uchar>( k ) = 255;
	bestHand.rankValues.push_back(k.y); // x=suit, y=value

	bestHand.name = "4 of a Kind";
	bestHand.rank = 7;

	return bestHand;
}

Hand Hand::getFullHouse( int trips, int pair1 ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int s=0; s<4; s++){
		Point q(s,trips);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back( trips ); // x=suit, y=value

	for(int s=0; s<4; s++){
		Point q(s,pair1);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back( pair1 ); // x=suit, y=value

	bestHand.name = "Full House";
	bestHand.rank = 6;

	return bestHand;
}

Hand Hand::getFlush( int suit ){
	Hand bestHand;
	Mat tHand = hand.clone();


	bestHand.name = "Flush";
	bestHand.rank = 5;

	return bestHand;
}

Hand Hand::getStraight( int run ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int v = run; v > run-5; v--){
		Point vi = getCardWithValue(v, tHand);
		bestHand.hand.at<uchar>( vi ) = 255;
		tHand.at<uchar>( vi ) = 0;
	}
	bestHand.rankValues.push_back( run );
	bestHand.name = "Straight";
	bestHand.rank = 4;

	return bestHand;
}

Hand Hand::get3ofAKind( int trips ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int s=0; s<4; s++){
		Point q(s,trips);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back(trips); // x=suit, y=value

	for(int i=0; i<2; i++){
		Point k = searchMatForKicker( tHand );
		bestHand.hand.at<uchar>( k ) = 255;
		bestHand.rankValues.push_back(k.y); // x=suit, y=value
	}

	bestHand.name = "3 of a kind";
	bestHand.rank = 3;

	return bestHand;
}

Hand Hand::get2Pairs( int pair1, int pair2 ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int s=0; s<4; s++){
		Point q(s,pair1);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back( pair1 ); // x=suit, y=value

	for(int s=0; s<4; s++){
		Point q(s,pair2);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back( pair2 ); // x=suit, y=value

	Point k = searchMatForKicker( tHand );
	bestHand.hand.at<uchar>( k ) = 255;
	bestHand.rankValues.push_back(k.y); // x=suit, y=value

	bestHand.name = "2 Pair";
	bestHand.rank = 2;

	return bestHand;
}

Hand Hand::get2ofAKind( int pair1 ){
	Hand bestHand;
	Mat tHand = hand.clone();

	for(int s=0; s<4; s++){
		Point q(s,pair1);
		if( tHand.at<uchar>( q ) == 255){
			bestHand.hand.at<uchar>( q ) = 255;
			tHand.at<uchar>( q ) = 0;
		}
	}
	bestHand.rankValues.push_back( pair1 ); // x=suit, y=value

	for(int i=0; i<2; i++){
		Point k = searchMatForKicker( tHand );
		bestHand.hand.at<uchar>( k ) = 255;
		bestHand.rankValues.push_back(k.y); // x=suit, y=value
	}

	bestHand.name = "Pair";
	bestHand.rank = 1;

	return bestHand;
}

Hand Hand::getHighCard(){
	Hand bestHand;
	Mat tHand = hand.clone();
	for(int i=0; i<5; i++){
		Point k = searchMatForKicker( tHand );
		bestHand.hand.at<uchar>( k ) = 255;
		bestHand.rankValues.push_back(k.y); // x=suit, y=value
	}

	bestHand.name = "High Card";
	bestHand.rank = 0;

	return bestHand;
}

int Hand::checkForRuns(){
	for(int v=13; v>4; v--){ // check downwards Ace - 5, no point starting search at 4
		if( matValueCount(v, hand) > 0){
			if( matValueCount(v-1, hand) > 0){
				if( matValueCount(v-2, hand) > 0){
					if( matValueCount(v-3, hand) > 0){
						if( matValueCount(v-4, hand) > 0){
							return v;
						}
					}
				}
			}
		}
	}
	return -1;
}

int Hand::checkForFlush(){
	for(int s=0; s<4; s++){
		if(matSuitCount(s, hand) >= 5){ // has a flush, straight flush is possible
			return s;
		}
	}
	return -1;
}

void Hand::checkForMatchingSets( int &pair1, int &pair2, int &trips, int &quads ){

	for(int v=13; v>0; v--){ // count Ace as high card and prioritize highest set, don't include Ace twice
		int vCnt = matValueCount(v, hand);
		if( vCnt == 1 || vCnt == 0){
			continue;
		}
		else if(vCnt == 2){
			if(pair1 == -1){
				pair1 = v;
			}
			else if(pair2 == -1){
				pair2 = v;
			}
		}
		else if(vCnt == 3 && trips == -1){
			trips = v;
		}
		else if(vCnt == 4 && quads == -1){
			quads = v;
		}
	}
}

Point Hand::searchMatForKicker( Mat &mat ){

	for(int v=13; v>0; v--){
		for(int s=0; s<4; s++){
			Point p(v,s);
			if( mat.at<uchar>(p) > 0){
				mat.at<uchar>(p) = 0;
				cout << "kicker: " << p << endl;
				return p;
			}
		}
	}
}

void Hand::printHand(Deck &deck){

	for(int s=0; s<4; s++){
		for(int v = 13; v>0; v--){
			Point c(s,v);
			if( hand.at<uchar>(c) == 255){
				deck.printCardName(c);
			}
		}
	}
}

void Hand::showHandMat(string name){
	namedWindow(name, WINDOW_NORMAL);
	imshow(name, hand);
	waitKey(0);
}

Point getCardWithValue(int v, Mat &mat){
	for(int s=0; s<4; s++){
		Point p(s,v);
		if( mat.at<uchar>(p) > 0){
			return p;
		}
	}
}

Point getCardWithSuit(int s, Mat &mat){
	for(int v=0; v<14; v++){
		Point p(s,v);
		if( mat.at<uchar>(p) > 0){
			return p;
		}
	}
}

void matClearNonSuit( int S, Mat &mat){
	for(int v=0; v<14; v++){
		for(int s=0; s<4; s++){
			if( s != S){
				Point p(s,v);
				mat.at<uchar>(p) = 0;
			}
		}
	}
}

int matSuitCount(int s, Mat &mat){
	int cnt = 0;
	for(int v=0; v<14; v++){
		Point p(s,v);
		if( mat.at<uchar>(p) > 0){
			cnt++;
		}
	}
	return cnt;
}

int matValueCount(int v, Mat &mat){
	int cnt = 0;
	for(int s=0; s<4; s++){
		Point p(s,v);
		if( mat.at<uchar>(p) > 0){
			cnt++;
		}
	}
	return cnt;
}
