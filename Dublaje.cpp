#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

double setBet(double credit);
string getColor(int color);
void jackpot(double bet, double& credit);
void addLevel(double bet, double& credit);
string getUsername();
int loadDoublingRB();

int main();

void dublaje(double &credit, int &dublajeRounds) {

	int betDigits = loadDoublingRB();
	if (betDigits > 4)
		cout << "\nHIGH NUMBER OF DIGITS FOR RANDOM BET!! BE CAREFUL WHILE BETTING\n";

	cout << "\n\nPlace color to 2 to exit DublajeRandom.\n\n";
	bool keepGoing = true;
	while (keepGoing && credit>0) {

		double nrDub = 0;
		double multiply = 0.1;
		for (int i = 0; i < betDigits; i++)
			multiply *= 10;

		for (int i = 0; i < betDigits; i++) {
			if (i==0 && betDigits!=1)
				nrDub += (rand() % 9+1) * multiply;
			else
				nrDub += rand() % 10 * multiply;
			multiply /= 10;
		}
		
		if (nrDub == 0) {
			double virgula = (rand() % 10) * 0.1;
			nrDub += virgula;
		}
		int culoare;
		int count = 0;
		double valoareInitiala = nrDub;

		if (valoareInitiala > credit) {
			valoareInitiala = credit;
			nrDub = credit;
		}
		cout << "\nNEW RANDOM BET: " << nrDub << "\n\n";

		while (nrDub) {

			if (count == 5) {
				cout << "\nYou reached the maximum number of doublings! \nCREDIT won: " << nrDub;
				credit += nrDub;
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
				break;
			}
			if (count == 0) 
				cout << "Color(0 for RED, 1 for BLACK, 2 for EXIT): ";
			else
				cout << "\nColor(0 for RED, 1 for BLACK, 2 for STOP): ";

			cin >> culoare;

			if (count == 0 && culoare == 2) {
				keepGoing = false;
				break;
			}

			if (count > 0 && culoare == 2) {
				cout << "\nSTOPPED! \nCREDIT won: " << nrDub;
				credit += nrDub;
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
				break;
			}

			int colorWin = rand() % 2;
			if (colorWin == culoare) {
				cout << "\nWIN!				Color: " << getColor(colorWin);
				nrDub *= 2;
				count++;
			}
			else {
				nrDub = 0;
				credit -= valoareInitiala;
				cout << "\nLOST!				Color: " << getColor(colorWin);
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
			}
			if (nrDub != 0)
				cout << "\nDoubling remaining: " << nrDub << endl;
		}

		
		std::cout << endl << "CREDIT remaining: " << credit << "\n";
		
	}
}

void dublajeCustom(double& credit, int& dublajeRounds) {

	cout << "\n\nPlace bet to 0 to exit DublajeCustom.\n\n";
	bool keepGoing = true;
	while (keepGoing && credit > 0) {

		double bet = setBet(credit);
		int culoare;
		int count = 0;
		float valoareInitiala = bet;

		if (valoareInitiala > credit) {
			valoareInitiala = credit;
			bet = credit;
		}
		if (bet == 0) {
			keepGoing = false;
			break;
		}

		while (bet) {

			if (count == 5) {
				std::cout << "\nYou reached the maximum number of doublings! \nCREDIT won: " << bet;
				credit += bet;
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
				break;
			}
			if (count==0)
				cout << "Color(0 for RED, 1 for BLACK): ";
			else
				cout << "\nColor(0 for RED, 1 for BLACK, 2 for STOP): ";

			cin >> culoare;

			if (count > 0 && culoare == 2) {
				cout << "\nSTOPPED! \nCREDIT won: " << bet;
				credit += bet;
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
				break;
			}

			int colorWin = rand() % 2;
			if (colorWin == culoare) {
				cout << "\nWIN!				Color: " << getColor(colorWin);
				bet *= 2;
				count++;
			}
			else {
				bet = 0;
				credit -= valoareInitiala;
				cout << "\nLOST!				Color: " << getColor(colorWin);
				dublajeRounds++;
				jackpot(valoareInitiala, credit);
				addLevel(valoareInitiala, credit);
			}
			if (bet !=0)
			cout << "\nDoubling remaining: " << bet << endl;
		}

		cout << endl << "CREDIT remaining: " << credit << "\n";
		
	}
}

int loadDoublingRB() {

	string username = getUsername();
	int randomBet = 1;
	ifstream getRB("accounts/" + username + "_drb.txt");
	getRB >> randomBet;
	if (randomBet < 1 && randomBet > 350)
		return 1;

	return randomBet;

}

string getColor(int color) {

	if (color == 0)
		return "RED";
	if (color == 1)
		return "BLACK";

	return "ERROR";
}