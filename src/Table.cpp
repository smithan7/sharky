/*
 * Table.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: andy
 */

#include "Table.h"

Table::Table(int nPlayers){
	for(int i=0; i<nPlayers; i++){
		players.push_back(i);
	}
	this->nPlayers = nPlayers;

	communityCards = Mat::zeros(14,4,CV_8UC1);
}

void Table::newHand(){
	communityCards = Mat::zeros(14,4,CV_8UC1);
	deck.newDeck();

	for(int i=0; i<nPlayers; i++){
		players[i].clearHand();
	}
}

void Table::drawCard(Point in){
	communityCards.at<uchar>(in) = 255;
}

void Table::dealHoleCards(){
	for(int i=0; i<nPlayers; i++){
		players[i].drawCard(deck.drawRandomCard());
		players[i].drawCard(deck.drawRandomCard());
	}
}

void Table::dealSpecificCard( int player, string suit, string value ){
	players[player].drawCard( deck.drawCardByName(suit, value) );

	if(player < 0){
		drawCard( deck.drawCardByName(suit, value) );
	}
}

void Table::showHands(){
	for(int i=0; i<nPlayers; i++){
		players[i].printHand(deck);
	}
}

void Table::showBestHands(){
	for(int i=0; i<nPlayers; i++){
		players[i].printBestHand(deck);
	}
}

void Table::dealFlop(){
	for(int i=0; i<3; i++){
		drawCard( deck.drawRandomCard() );
	}
}

void Table::makePlayerHands(){
	for(size_t i=0; i<players.size(); i++){
		players[i].makeBestHand( communityCards );
	}
}

void Table::showCommunityCards(){
	cout << "Community cards: " << endl;

	for(int i=0; i<communityCards.cols; i++){
		for(int j=0; j<communityCards.rows; j++){
			Point p(i,j);
			if(communityCards.at<uchar>(p) == 255){
				cout << "   ";
				deck.printCardName(p);
			}
		}
	}
}

vector<int> Table::getWinningHand(){

	int bestRank = -1;
	vector<int> winningPlayers;
	for(size_t i=0; i<nPlayers; i++){
		if(players[i].bestHand.rank > bestRank){
			bestRank = players[i].bestHand.rank;
			winningPlayers.clear();
			winningPlayers.push_back(i);
		}
		else if(players[i].bestHand.rank == bestRank){
			winningPlayers.push_back(i);
		}
	}
	if(winningPlayers.size() == 1){
		return winningPlayers;
	}
	else{
		bestRank = -1;
		int iter = 0;
		int rankLength = players[ winningPlayers[0] ].bestHand.rankValues.size();
		while(winningPlayers.size() > 1 && iter < rankLength ){
			vector<int> wp;
			for(size_t i=0; i<winningPlayers.size(); i++){
				cout << winningPlayers[i] << ": " << players[ winningPlayers[i] ].bestHand.rankValues[iter] << endl;
				if(players[ winningPlayers[i] ].bestHand.rankValues[iter] > bestRank){
					cout << i << " has bestHandRank" << endl;
					bestRank = players[ winningPlayers[i] ].bestHand.rankValues[iter];
					wp.clear();
					wp.push_back( winningPlayers[i] );
				}
				else if(players[ winningPlayers[i] ].bestHand.rankValues[iter] == bestRank){
					wp.push_back( winningPlayers[i] );
				}
			}

			winningPlayers.clear();
			winningPlayers = wp;
			iter++;
		}
		return winningPlayers;
	}

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}

