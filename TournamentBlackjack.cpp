#include <iostream>
#include <string>

using namespace std;

int main();

double setBet(double credit);
void generatetDealerCards(int* tDealerCards, int& tDealerPos, int& tDealerPoints, int& taceD);
void generatetPlayerCards(int* tPlayerCards, int& tPlayerPos, int& tPlayerPoints, int& taceP);
void getTCards(int* tPlayerCards, int tPlayerPos, int tPlayerPoints);
int checkTCard(int card, int points, int& ace);
string verifyTCard(int card);
void matchTSummary(int* tPlayerCards, int* tDealerCards, int tPlayerPos, int tDealerPos, int tPlayerPoints, int tDealerPoints, string status, int tournamentPlayerWins, int tournamentDealerWins, int tournamentMatch);
void jackpot(double bet, double& credit);
string getRoundStatus(int tournamentMatch);
string getUsername();
void tournamentsSummary(string status, double credit, double bet);
void addLevel(double bet, double& credit);


void tournamentBlackjack(double& credit, int& tblackjackRounds, int& tblackjackWins) {


	cout << "\nSet BET to 0 to exit Blackjack Tournament\n\n";

	double bet = setBet(credit); cout << "\n";
	double tournamentBet = bet / 50;
	bool keepGoing = true;
	int* tPlayerCards = new int[5];
	int* tDealerCards = new int[5];
	int tournamentPlayerWins = 0;
	int tournamentDealerWins = 0;
	int tournamentRounds = 0;
	int tournamentMatch = 1;

	while (keepGoing && bet !=0) {

		tournamentRounds++;
		cout << "\nGame: " << tournamentRounds << "\n";
		cout << "Round: " << getRoundStatus(tournamentMatch) << "\n\n";
		int tPlayerPos = 0, tDealerPos = 0;
		int tPlayerPoints = 0, tDealerPoints = 0, taceP = 0, taceD = 0;

		generatetDealerCards(tDealerCards, tDealerPos, tDealerPoints, taceD);
		generatetPlayerCards(tPlayerCards, tPlayerPos, tPlayerPoints, taceP);


		if ((tPlayerPoints == tDealerPoints) || (tPlayerPoints > 21 && tDealerPoints > 21)) {
	
			matchTSummary(tPlayerCards, tDealerCards, tPlayerPos, tDealerPos, tPlayerPoints, tDealerPoints, "TIED", tournamentPlayerWins, tournamentDealerWins, tournamentMatch);
			tournamentRounds--;
		}
		else if (((tPlayerPoints > tDealerPoints) || tDealerPoints > 21) && (tPlayerPoints <= 21)) {
	
			tournamentPlayerWins++;
			matchTSummary(tPlayerCards, tDealerCards, tPlayerPos, tDealerPos, tPlayerPoints, tDealerPoints, "WIN", tournamentPlayerWins, tournamentDealerWins, tournamentMatch);
		
		}
		else if (((tPlayerPoints < tDealerPoints) || tPlayerPoints > 21) && (tDealerPoints <= 21)) {
		
			tournamentDealerWins++;
			matchTSummary(tPlayerCards, tDealerCards, tPlayerPos, tDealerPos, tPlayerPoints, tDealerPoints, "LOSE", tournamentPlayerWins, tournamentDealerWins, tournamentMatch);
			
		}
		else {
			cout << "\nError occurred.\n";
		}

		// check who wins the round

		if (tournamentPlayerWins == 5) {
			tournamentPlayerWins = 0;
			tournamentDealerWins = 0;
			tournamentRounds = 0;
			tournamentMatch++;
			
			
			if (tournamentMatch == 6) {
				credit += bet * 16;
				tournamentsSummary("WIN", credit, bet);
				jackpot(bet, credit);
				addLevel(bet*16, credit);
				tblackjackWins++;
				tblackjackRounds++;
				break;
				//win tourney
			}
			cout << "\n\nYou have advanced to the next round!\n\n";
		}
		else if(tournamentDealerWins == 5) {
			credit -= bet;
			tournamentsSummary("LOSE", credit, bet);
		//	cout << "\n\nYou have been eliminated!\n\n";
			jackpot(bet, credit);
			addLevel(bet, credit);
			tblackjackRounds++;
			break;
		}
		
	}
	

	delete[] tPlayerCards;
	delete[] tDealerCards;
}

void generatetPlayerCards(int* tPlayerCards, int& tPlayerPos, int& tPlayerPoints, int& taceP) {

	int action;
	for (int i = 0; i < 2; i++) {
		tPlayerCards[i] = rand() % 13 + 1;
		tPlayerPoints += checkTCard(tPlayerCards[i], tPlayerPoints, taceP);
		tPlayerPos++;
	}
	getTCards(tPlayerCards, tPlayerPos, tPlayerPoints);
	if (tPlayerPoints == 21)
		return;
	cin >> action; cout << "\n";

	while (action && tPlayerPos < 5) {

		if (tPlayerPoints <= 20 && taceP >= 1) {
			tPlayerPoints -= 10;
			taceP--;
		}

		tPlayerCards[tPlayerPos] = rand() % 13 + 1;
		tPlayerPoints += checkTCard(tPlayerCards[tPlayerPos], tPlayerPoints, taceP);
		tPlayerPos++;

		if (tPlayerPos < 5 && tPlayerPoints < 21) {
			getTCards(tPlayerCards, tPlayerPos, tPlayerPoints);
			cin >> action; cout << "\n";
		}
		else {
			getTCards(tPlayerCards, tPlayerPos, tPlayerPoints);
			break;
		}
	}


}

void getTCards(int* tPlayerCards, int tPlayerPos, int tPlayerPoints) {

	cout << "CARDS: | ";
	for (int i = 0; i < tPlayerPos; i++) {
		cout << verifyTCard(tPlayerCards[i]) << " | ";
	}
	cout << "\nPoints: " << tPlayerPoints << "\n";
	if (tPlayerPos == 21)
		return;
	if (tPlayerPos < 5 && tPlayerPoints < 21)
		cout << "\n\n0 for STOP, 1 for ANOTHER CARD: ";

}

string verifyTCard(int card) {

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

void generatetDealerCards(int* tDealerCards, int& tDealerPos, int& tDealerPoints, int& taceD) {

	for (int i = 0; i < 2; i++) {
		tDealerCards[i] = rand() % 13 + 1;
		tDealerPoints += checkTCard(tDealerCards[i], tDealerPoints, taceD);
		tDealerPos++;
	}

	while (tDealerPoints <= 11 && tDealerPos < 5) {

		if (tDealerPoints <= 20 && taceD >= 1) {
			tDealerPoints -= 10;
			taceD--;
		}

		tDealerCards[tDealerPos] = rand() % 13 + 1;
		tDealerPoints += checkTCard(tDealerCards[tDealerPos], tDealerPoints, taceD);
		tDealerPos++;
	}

	int randomAction = rand() % 6 + 11;
	if (tDealerPos < 5 && tDealerPoints < randomAction) {
		tDealerCards[tDealerPos] = rand() % 13 + 1;
		tDealerPoints += checkTCard(tDealerCards[tDealerPos], tDealerPoints, taceD);
		tDealerPos++;


	}

}

int checkTCard(int card, int points, int& ace) {

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
string getRoundStatus(int tournamentMatch) {

	if (tournamentMatch == 5)
		return "FINAL";
	if (tournamentMatch == 4)
		return "SEMI-FINAL";
	if (tournamentMatch == 3)
		return "QUARTER-FINAL";
	if (tournamentMatch == 2)
		return "2";
	if (tournamentMatch == 1)
		return "1";
	return "ERROR";

}

void matchTSummary(int* tPlayerCards, int* tDealerCards, int tPlayerPos, int tDealerPos, int tPlayerPoints, int tDealerPoints, string status, int tournamentPlayerWins, int tournamentDealerWins, int tournamentMatch) {

	int zece = 0;
	int spatiu = 0;

	cout << "\n\n################################# GameSummary #################################\n\n";

	cout << "Status: " << status;

	cout << "\n\nDealer Cards: | ";
	for (int i = 0; i < tDealerPos; i++) {
		cout << verifyTCard(tDealerCards[i]) << " | ";
		if (tDealerCards[i] == 10)
			zece++;
	}


	for (int i = 0; i < tDealerPos; i++) {
		cout << "    ";
	}

	cout << "Your cards: | ";
	for (int i = 0; i < tPlayerPos; i++) {
		cout << verifyTCard(tPlayerCards[i]) << " | ";
	}
	cout << "\nDealer Points: " << tDealerPoints;
	cout << "       ";
	for (int i = 0; i < tDealerPos; i++) {
		cout << "    ";
		if (i > 1)
			cout << "    ";
		if (zece > 0) {
			cout << " ";
			zece--;
		}
	}
	cout << "Your Points: " << tPlayerPoints;

	cout << "\n\n";
	if (status == "LOSE") {
		cout << "Player game wins: " << tournamentPlayerWins << "\n";
		cout << "Enemy game wins: " << tournamentDealerWins;
	}
	else if (status == "WIN") {
		cout << "Player game wins: " << tournamentPlayerWins << "\n";
		cout << "Enemy game wins: " << tournamentDealerWins;
	}
	else {
		cout << "This round is going to be repeated!";
	}
	cout << "\n\nROUND: " << getRoundStatus(tournamentMatch);

	cout << "\n\n################################# GameSummary #################################\n\n";
	system("PAUSE");
}

void tournamentsSummary(string status, double credit, double bet) {

	cout << "\n\n################################# TournamentSummary #################################\n\n";
	cout << "Status: " << status << "\n\n";
	if (status == "WIN") {
		cout << "Winner: " << getUsername();
		cout << "\n\nCREDIT won: " << bet * 16;
		cout << "\nCREDIT remaining: " << credit;
	}
	else {
		cout << "Winner: BOT_NUMBER" << rand()%1000;
		cout << "\n\nCREDIT lost: " << bet;
		cout << "\nCREDIT remaining: " << credit;
	}

	cout << "\n\n################################# TournamentSummary #################################\n\n";

}