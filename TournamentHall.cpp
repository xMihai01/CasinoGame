#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string getUsername();
bool checkForPass(double& credit, int slotsRounds, int blackjackRounds, string username);
void tournamentMenu(double& credit, int tblackjackRounds, int tblackjackWins, int tslotsRounds, int tslotsWins);
void updateCredit(double credit);

void updateTournamentGames(int tblackjackRounds, int tblackjackWins, int tslotsRounds, int tslotsWins);
void setTournamentGames(int& tblackjackRounds, int& tblackjackWins, int& tslotsRounds, int& tslotsWins);

void tournamentBlackjack(double& credit, int& tblackjackRounds, int& tblackjackWins);
void tournamentSlots(double& credit, int& tslotsRounds, int& tslotsWins);



void tournamentHall(double& credit, int slotsRounds, int blackjackRounds) {

	string username = getUsername();
	int tblackjackRounds = 0, tblackJackWins = 0;
	int tslotsRounds = 0, tslotsWins = 0;

	if (!checkForPass(credit, slotsRounds, blackjackRounds, username)) {
		//cout << "\n\nYou are not allowed to enter the TournamentHall\n\n";
		return;
	}
	setTournamentGames(tblackjackRounds, tblackJackWins, tslotsRounds, tslotsWins);
	int alg;
	bool keepGoing = true;
	tournamentMenu(credit, tblackjackRounds, tblackJackWins, tslotsRounds, tslotsWins);

	while (keepGoing && credit) {

		cout << "\nTournament (-1 for info): "; cin >> alg;

		switch (alg) {
		case 1:
			tournamentBlackjack(credit, tblackjackRounds, tblackJackWins);

			break;
		case 2:
			//cout << "\nCOMING SOON\n";
			tournamentSlots(credit, tslotsRounds, tslotsWins);

			break;
		case 0:
			keepGoing = false;
			break;
		default:
			tournamentMenu(credit, tblackjackRounds, tblackJackWins, tslotsRounds, tslotsWins);
			break;
		}
		updateCredit(credit);
		updateTournamentGames(tblackjackRounds, tblackJackWins, tslotsRounds, tslotsWins);
	}

}

void tournamentMenu(double& credit, int tblackjackRounds, int tblackjackWins, int tslotsRounds, int tslotsWins) {

	cout << "\n\n#################### TournamentHall ####################\n\n";

	cout << "CREDIT: " << credit;
	cout << "\n\nTournaments played: " << tblackjackRounds+tslotsRounds;
	cout << "\nTournaments won: " << tblackjackWins+tslotsWins;

	cout << "\n\nPress 0 to exit TournamentHall.\n";
	cout << "Press 1 to join a Blackjack Tournament.\n";
	cout << "Press 2 to join a Slots Tournament.";

	cout << "\n\n#################### TournamentHall ####################\n\n";

}

bool checkForPass(double &credit, int slotsRounds, int blackjackRounds, string username) {

	ifstream checkPass("userdata/" + username + "_pass.txt");
	int verify;
	if (!(checkPass >> verify)) {


		cout << "\n\nYou are not allowed to enter the TournamentHall.";
		cout << "\nPress 1 for more info and 0 to exit: ";
		cin >> verify;

		if (verify == 1) {
			cout << "\n\n########################################\n\n";

			cout << "Requirements to get access to the TournamentHall: \n\n";
			cout << "50.000 CREDITS (Must have 100.000 at purchase moment)\n";
			cout << "200 Blacjack games played\n";
			cout << "1000 Slots games played\n\n";
			
			cout << "Press 1 to buy access to the TournamentHall and 0 to exit.";

			cout << "\n\n########################################\n\n";
			cout << "BUY: ";
			cin >> verify;

			if (verify == 1) {
				
				if ((credit >= 100000 && slotsRounds >=1000) && blackjackRounds >=200) {
					cout << "\nSuccessfully purchased access to the TournamentHall!\n";
					ofstream getPass("userdata/" + username + "_pass.txt");
					getPass << 100;
					credit -= 50000;
					updateCredit(credit);
					return true;
				}
				else {
					cout << "\nYour account doesn't meet the requirements needed to purchase access to the TournamentHall!\n\n";
			
				}

			}

		}

	}
	else {

		checkPass >> verify;
		if (verify == 100)
			return true;
		cout << "\n\nAn error ocurred, please delete " << username << "_pass.txt file.\n\n";

	}
	return false;
}
