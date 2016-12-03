//============================================================================
// Name        : shark.cpp
// Author      : andy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Deck.h"
#include "Player.h"
#include "Table.h"

using namespace std;

void learnStartingHand(Mat startingHandProb);


int main() {


	need to make it always! use hole cards, right now it doesn't

	srand(time(NULL));

	int nPlayers = 2;
	Table table(nPlayers);


	//Mat a = Mat::ones(52,52,CV_32F)*0.5;
	//Mat a = imread("startingHandProbability.jpg", CV_32F);

	//learnStartingHand(a);

	// deal hole cards
	table.dealHoleCards();

	//table.dealSpecificCard( 0, "Diamonds", "Ace");
	//table.dealSpecificCard( 0, "Spades", "Ace");
	//table.dealSpecificCard( 0, "Clubs", "Ace");
	//table.dealSpecificCard( 0, "Hearts", "Ace");
	//table.dealSpecificCard( 0, "Diamonds", "10");

	//table.dealSpecificCard( 1, "Diamonds", "6");
	//table.dealSpecificCard( 1, "Spades", "6");
	//table.dealSpecificCard( 1, "Clubs", "6");
	//table.dealSpecificCard( 1, "Hearts", "6");
	//table.dealSpecificCard( 1, "Diamonds", "9");

	table.players[0].showHandMat();
	table.deck.showDeck();
	table.showHands();

	cout << "**************" << endl;

	// deal flop
	table.dealFlop();

	// deal the turn
	table.drawCard(table.deck.drawRandomCard() );

	// deal the river
	table.drawCard(table.deck.drawRandomCard());
	table.showCommunityCards();
	table.deck.showDeck();

	cout << "All Cards Delt*******************************************************" << endl;

	table.makePlayerHands();

	for(size_t i=0; i<table.players.size(); i++){
		table.players[i].showHandMat();
		table.players[i].showBestHandMat();
		table.players[i].printBestHand(table.deck);
		cout << "hand: " << table.players[i].bestHand.name << endl;
		cout << "rank: " << table.players[i].bestHand.rank << endl;
		cout << "rankValues: ";
		for(size_t j=0; j<table.players[i].bestHand.rankValues.size(); j++){
			cout << table.players[i].bestHand.rankValues[j] << ", ";
		}
		cout << endl;
	}
	waitKey(1);

	vector<int> winner = table.getWinningHand();

	table.players[winner[0]].showBestHandMat();
	waitKey(1);
	table.players[winner[0]].printBestHand(table.deck);



	cout << "winner is player: " << winner[0] << " with a " << table.players[winner[0]].bestHand.name << endl;

	return 0;
}


/*
void learnStartingHand(Mat startingHandProb){

	float learningRate = 0.01;
	int numRounds = 100;
	float numIter = 100;
	int nPlayers = 2;

	for(int rounds = 0; rounds < numRounds; rounds++){
		cout << "Round: " << rounds+1 << endl;
		int numWins;
		for(int d0 = 0; d0<51; d0++){
			for(int d1 = d0; d1<52; d1++){

				Point c(d0,d1);
				Point ci(d1,d0);

				if(d0 != d1){
					numWins = 0;
					for(int iter = 0; iter<numIter; iter++){

						Deck cards;
						vector<Player> players;
						Table table;

						for(int i=0; i<nPlayers; i++){
							Player t(i);
							players.push_back(t);
						}

						players[0].drawCard(cards.drawSpecificCard(d0));
						players[0].drawCard(cards.drawSpecificCard(d1));

						// deal hole cards
						for(int i=1; i<nPlayers; i++){
							players[i].drawCard(cards.drawRandomCard());
							players[i].drawCard(cards.drawRandomCard());
						}


						// deal flop
						for(int i=0; i<5; i++){
							table.drawCard(cards.drawRandomCard());
						}
						//cout << "All Cards Delt*******************************************************" << endl;
						//table.showCards();


						for(size_t i=0; i<players.size(); i++){
							players[i].makeBestHand(table.communityCards);

						}

						for(int i=0; i<nPlayers; i++){
							table.showdownHands.push_back(players[i].bestHand);
							table.showdownHandsRank.push_back(players[i].handRank);
						}
						vector<int> winner = table.chooseBestHand();



						for(size_t j=0; j<winner.size(); j++){
							if(winner[j] == 0){
								numWins++;
							}
						}
					}
					float mProb = numWins / numIter;
					startingHandProb.at<float>(c) += learningRate*(mProb - startingHandProb.at<float>(c));
					startingHandProb.at<float>(ci) = startingHandProb.at<float>(c);
				}
				else{
					startingHandProb.at<float>(c) = -1;
					startingHandProb.at<float>(ci) = -1;
				}
			}
		}
	}

	int maxi[2];
	float maxv = -1;
	int mini[2];
	float minv = 2;

	for(int i=0; i<52; i++){
		for(int j=0; j<52; j++){
			Point c(i,j);
			if(startingHandProb.at<float>(c) > maxv){
				maxv = startingHandProb.at<float>(c);
				maxi[0] = i;
				maxi[1] = j;
			}
			else if(startingHandProb.at<float>(c) < minv && i!=j){
				minv = startingHandProb.at<float>(c);
				mini[0] = i;
				mini[1] = j;
			}
			cout << startingHandProb.at<float>(c) << ", ";

		}
		cout << endl;
	}

	Deck maxD;
	Card m = maxD.drawSpecificCard(maxi[0]);
	Card m2 = maxD.drawSpecificCard(maxi[1]);

	cout << "best hand: " << m.value << " of " << m.suit << " and " << m2.value << " of " << m2.suit << " with maxv: " << maxv << endl;
	Deck minD;
	Card mi = minD.drawSpecificCard(mini[0]);
	Card mi2 = minD.drawSpecificCard(mini[1]);
	cout << "worst hand: " << mi.value << " of " << mi.suit << " and " << mi2.value << " of " << mi2.suit << " with minv : " << minv << endl;

	imwrite("startingHandProbability.jpg", startingHandProb);

}
*/
