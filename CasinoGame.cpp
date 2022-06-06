#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
int logOut = 0;
int dublajeRounds = 0;
int lotoRounds = 0;
int ruletaRounds = 0;
int slotsRounds = 0;
int blackjackRounds = 0;
int barbutRounds = 0;


// SYSTEM

double setCredit();
double setCreditNew();
void updateCredit(double credit);
void updateGames(int lotoRounds, int dublajeRounds, int ruletaRounds, int slotsRounds, int blackjackRounds, int barbutRounds);
void setGamesPlayed(int& lotoRounds, int& dublajeRounds, int& ruletaRounds,
	int& slotsRounds, int& blackjackRounds, int& barbutRounds);
double setBet(double credit);
void welcome();
void info();
void rejoin(double& credit);
bool loggedIn();

// SHOP

void shopMenu(double& credit);

// SETTINGS

void settingsMenu(int &logOut);

// LEVELS

int getLevel();
double getEXP();
double getRequiredEXP(int level, double experience);

//LOTO
//void loto(double& credit, double bet, int* winningNumbers, int* choices, int& lotoRounds, int* foundNumber);
void loto(double& credit, int& lotoRounds);

//DUBLAJE
void dublaje(double& credit, int& dublajeRounds);
void dublajeCustom(double& credit, int& dublajeRounds);

//RULETA
void ruleta(double& credit, int& ruletaRounds);

//SLOTS
void slots(double& credit, int& slotsRounds);

//Blackjack
void blackjack(double& credit, int& blackjackRounds);
void tournamentBlackjack(double& credit);

//Barbut

void barbut(double& credit, int& barbutRounds);

// JACKPOTGAME

void jackpotGame(double& credit);

//TournamentHall
void tournamentHall(double& credit, int slotsRounds, int blackjackRounds);

// MINGIAMES

void minigamesMenu(double& credit);

int main()
{
	
	if (!loggedIn())
		return 0;


	double credit = setCreditNew();
	bool gamePlay = true;
	setGamesPlayed(lotoRounds, dublajeRounds, ruletaRounds, slotsRounds, blackjackRounds, barbutRounds);

	if (credit == 0) {
		cout << "\n\nThis account is out of credits!\nMake a new one to keep playing.\n\n";
		system("PAUSE");
		return 0;
	}

	welcome();
	srand(time(NULL));

	cout << "\n\n";
	
	while (gamePlay && credit>0) {
		
		cout << "Game (-1 for info): ";
		int alg, alegereTipDublaj;
		cin >> alg;

		switch (alg) {
		case 1:
			loto(credit, lotoRounds);
			rejoin(credit);
			break;
		case 2:
			cout << "Press 1 for random Dublaje.\nPress 2 for Custom Dublaje.\nDublaje: ";
			cin >> alegereTipDublaj;
			if (alegereTipDublaj == 1) {
				dublaje(credit, dublajeRounds);
			} else if (alegereTipDublaj == 2) {
				dublajeCustom(credit, dublajeRounds);
			} else {
				cout << "Invalid type, returning to start..\n\n";
			}
			rejoin(credit);
			break;
		case 3:
			ruleta(credit, ruletaRounds);
			rejoin(credit);
			break;
		case 4:
			slots(credit, slotsRounds);
			rejoin(credit);
			break;
		case 5:
			blackjack(credit, blackjackRounds);
			rejoin(credit);
			break;
		case 6:
			barbut(credit, barbutRounds);
			rejoin(credit);
			break;
		case 0:
			updateCredit(credit);
			updateGames(lotoRounds, dublajeRounds, ruletaRounds, slotsRounds, blackjackRounds, barbutRounds);
			gamePlay = false;
			break;
		case 99:
			settingsMenu(logOut);
			break;
		case 100:
			tournamentHall(credit, slotsRounds, blackjackRounds);
			rejoin(credit);
			break;
		case 101:
			shopMenu(credit);
			rejoin(credit);
			break;
		case 102:
			minigamesMenu(credit);
			rejoin(credit);
			break;
		default:
			info();
			break;
		}

		if (logOut == 1) {
			cout << "\nYou have been logged out!\n\n\n";
			system("PAUSE");
			return 0;
		}

		updateCredit(credit);
		updateGames(lotoRounds, dublajeRounds, ruletaRounds, slotsRounds, blackjackRounds, barbutRounds);
	}

	if (credit <= 0) {
		cout << "You have no credits left!\nRestart the game and make a new account in order to keep playing!\n\n";
		updateCredit(0);
		updateGames(lotoRounds, dublajeRounds, ruletaRounds, slotsRounds, blackjackRounds, barbutRounds);
		system("PAUSE");
		return 0;
	}

	cout << "\n\nThe game has stopped and everything was successfully saved!\n\n";
	system("PAUSE");

	return 0;
}

void rejoin(double& credit) {

	int level = getLevel();
	double exp = getEXP();

	cout << "\n\n#################### CasinoStats ####################\n\n";

	cout << "CREDIT: " << credit << "\n";
	cout << "LEVEL: " << level << "\n";
	cout << "EXPERIENCE: " << exp << " (" << getRequiredEXP(level, exp)-exp << " more to LEVEL UP) \n\n";
	cout << "Played Loto: " << lotoRounds << "\n";
	cout << "Played Dublaje: " << dublajeRounds << "\n";
	cout << "Played Ruleta: " << ruletaRounds << "\n";
	cout << "Played Slots: " << slotsRounds << "\n";
	cout << "Played Blackjack: " << blackjackRounds << "\n";
	cout << "Played Barbut: " << barbutRounds << "\n\n";


	cout << "#################### CasinoStats ####################\n\n";
}