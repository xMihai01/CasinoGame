#include <iostream>

using namespace std;

double setBet(double credit);

void generateRandomZar(int& opponent);
void roundSummaryBarbut(int player, int dealer, string status, double bet, double credit);
void jackpot(double bet, double& credit);
void addLevel(double bet, double& credit);

void barbut(double& credit, int& barbutRounds) {

	cout << "\n\nWARNING! Placing the bet will automatically roll the dices!";
	cout << "\nSet the BET to 0 to exit Barbut.\n\n";
	double bet;
	int player, dealer;

	while (credit) {
		
		bet = setBet(credit); cout << "\n";
		
		if (bet == 0) {
			break;
		}

		generateRandomZar(player);
		generateRandomZar(dealer);

		if (player == 2)
			player = 13;
		if (dealer == 2)
			dealer = 13;

		if (player > dealer) {
			credit += bet;
			roundSummaryBarbut(player, dealer, "WIN", bet, credit);
		}
		else if (player < dealer) {
			credit -= bet;
			roundSummaryBarbut(player, dealer, "LOSE", bet, credit);
		}
		else {
			roundSummaryBarbut(player, dealer, "TIE", bet, credit);
		}

		jackpot(bet, credit);
		addLevel(bet, credit);
		barbutRounds++;
	}

}

void generateRandomZar(int& opponent) {

	opponent = 0;
	for (int i = 0; i < 2; i++) {
		opponent += rand() % 6 + 1;
	}

}

void roundSummaryBarbut(int player, int dealer, string status, double bet, double credit) {

	cout << "\n\n################################# RoundSummary #################################\n\n";

	cout << "Status: " << status << "\n\n";


	cout << "Dealer dice points: ";
	if (dealer == 13)
		cout << "2";
	else
		cout << dealer;
	cout << "		Your dice points: ";
	if (player == 13)
		cout << "2";
	else
		cout << player;
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