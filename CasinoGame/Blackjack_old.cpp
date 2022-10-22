#include <iostream>
#include <string>

using namespace std;

int main();

double setBet(double credit);
void generateDealerCards(int *dealerCards, int& dealerPos, int &dealerPoints, int &aceD);
void generatePlayerCards(int* playerCards, int &playerPos, int &playerPoints, int &aceP);
void getCards(int* playerCards, int playerPos, int playerPoints);
int checkCard(int card, int points, int& ace);
string verifyCard(int card);
void matchSummary(int *playerCards, int *dealerCards, int playerPos, int dealerPos, int playerPoints, int dealerPoints, string status, double credit, double bet);
void jackpot(double bet, double& credit);
void addLevel(double bet, double& credit);


void blackjack(double& credit, int& blackjackRounds) {


	cout << "\nSet BET to 0 to exit Blackjack\n\n";

	double bet;
	int* playerCards = new int[5];
	int* dealerCards = new int[5];
	

	// 0,A,2,3,4,5,6,7,8,9,10,J,Q,K

	while (credit) {

		bet = setBet(credit); cout << "\n";
		if (bet == 0)
			break;
		int playerPos = 0, dealerPos = 0;
		int playerPoints = 0, dealerPoints = 0, aceP = 0, aceD = 0;

		generateDealerCards(dealerCards, dealerPos, dealerPoints, aceD);
		generatePlayerCards(playerCards, playerPos, playerPoints, aceP);


		if ((playerPoints == dealerPoints) || (playerPoints > 21 && dealerPoints > 21)) {

			matchSummary(playerCards, dealerCards, playerPos, dealerPos, playerPoints, dealerPoints, "TIED", credit, bet);
		}
		else if (((playerPoints > dealerPoints) || dealerPoints >21) && (playerPoints <=21)) {

			credit += bet;
			matchSummary(playerCards, dealerCards, playerPos, dealerPos, playerPoints, dealerPoints, "WIN", credit, bet);

		}
		else if (((playerPoints < dealerPoints) || playerPoints>21) && (dealerPoints <=21)) {
			
			credit -= bet;
			matchSummary(playerCards, dealerCards, playerPos, dealerPos, playerPoints, dealerPoints, "LOSE", credit, bet);

		}
		else {
			cout << "\nError occurred.\n";
		}
		jackpot(bet, credit);
		blackjackRounds++;
		addLevel(bet, credit);
	}
	

	delete[] playerCards;
	delete[] dealerCards;
}

void generatePlayerCards(int* playerCards, int& playerPos, int& playerPoints, int& aceP) {

	int action;
	for (int i = 0; i < 2; i++) {
		playerCards[i] = rand() % 13 + 1;
		playerPoints += checkCard(playerCards[i], playerPoints, aceP);
		playerPos++;
	}
	getCards(playerCards, playerPos, playerPoints);
	if (playerPoints == 21)
		return;
	cin >> action; cout << "\n";
	
	while (action && playerPos < 5) {

		if (playerPoints <= 20 && aceP >= 1) {
			playerPoints -= 10;
			aceP--;
		}

		playerCards[playerPos] = rand() % 13 + 1;
		playerPoints += checkCard(playerCards[playerPos], playerPoints, aceP);
		playerPos++;

		if (playerPos < 5 && playerPoints <21) {
			getCards(playerCards, playerPos, playerPoints);
			cin >> action; cout << "\n";
		}
		else {
			getCards(playerCards, playerPos, playerPoints);
			break;
		}
	}


}

void getCards(int* playerCards, int playerPos, int playerPoints) {

	cout << "CARDS: | ";
	for (int i = 0; i < playerPos; i++) {
		cout << verifyCard(playerCards[i]) << " | ";
	}
	cout << "\nPoints: " << playerPoints << "\n";
	if (playerPos == 21)
		return;
	if (playerPos < 5 && playerPoints <21)
	cout << "\n\n0 for STOP, 1 for ANOTHER CARD: ";

}

string verifyCard(int card) {

	if (card >= 2 && card <= 10)
		return to_string(card);
	if (card == 11)
		return "J";
	if (card == 12)
		return "Q";
	if (card == 13)
		return "K";
	if (card == 1) {
		return "A";
	}
	return "ERROR";

}

void generateDealerCards(int* dealerCards, int& dealerPos, int& dealerPoints, int& aceD) {

	for (int i = 0; i < 2; i++) {
		dealerCards[i] = rand() % 13 + 1;
		dealerPoints += checkCard(dealerCards[i], dealerPoints, aceD);
		dealerPos++;
	}

	while (dealerPoints <= 11 && dealerPos <5) {

		if (dealerPoints <= 20 && aceD >= 1) {
			dealerPoints -= 10;
			aceD--;
		}

		dealerCards[dealerPos] = rand() % 13 + 1;
		dealerPoints += checkCard(dealerCards[dealerPos], dealerPoints, aceD);
		dealerPos++;
	}
	
	int randomAction = rand() % 6 + 11;
	if (dealerPos < 5 && dealerPoints < randomAction) {
		dealerCards[dealerPos] = rand() % 13 + 1;
		dealerPoints += checkCard(dealerCards[dealerPos], dealerPoints, aceD);
		dealerPos++;


	}

}

int checkCard(int card, int points, int& ace) {

	if (card >= 2 && card <= 10)
		return card;
	if (card > 10)
		return 10;
	if (card == 1) {

		if (points < 11) {
			ace++;
			return 11;
		}
		else
			return 1;
	}
	return -1000;

}

void matchSummary(int* playerCards, int* dealerCards, int playerPos, int dealerPos, int playerPoints, int dealerPoints, string status, double credit, double bet) {

	int zece = 0;
	int spatiu = 0;

	cout << "\n\n################################# RoundSummary #################################\n\n";

	cout << "Status: " << status;

	cout << "\n\nDealer Cards: | ";
	for (int i = 0; i < dealerPos; i++) {
		cout << verifyCard(dealerCards[i]) << " | ";
		if (dealerCards[i] == 10)
			zece++;
	}
	
	for (int i = 0; i < dealerPos; i++) {
		cout << "    ";
	}

	cout << "Your cards: | ";
	for (int i = 0; i < playerPos; i++) {
		cout << verifyCard(playerCards[i]) << " | ";
	}
	cout << "\nDealer Points: " << dealerPoints;
	cout << "       ";
	for (int i = 0; i < dealerPos; i++) {
		cout << "    ";
		if (i > 1)
			cout << "    ";
		if (zece > 0) {
			cout << " ";
			zece--;
		}
	}
	cout << "Your Points: " << playerPoints;

	cout << "\n\n";
	if (status == "LOSE") {
		cout << "CREDIT lost: " << bet << "\n";
		cout << "CREDIT remaining " << credit;
	}
	else if (status == "WIN") {
		cout << "CREDIT won: " << bet << "\n";
		cout << "CREDIT remaining " << credit;
	}
	else {
		cout << "You didn't lose/win any credits!";
	}

	cout << "\n\n################################# RoundSummary #################################\n\n";
}