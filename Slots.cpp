#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main();
string getUsername();

double setBet(double credit);
void generateSlotsResult(int **slotsResult);
void reviewSlotsResult(int** slotsResult);
void checkSlotsResult(int** slotsResult, double &credit, double bet, int enableDoubling);
void checkSlotsWin(int value, double bet, double& winnings, double &criteria);
void jackpot(double bet, double& credit);
int loadSlotsSettingsDSS();
void addLevel(double bet, double& credit);

void slots(double& credit, int& slotsRounds) {

	cout << "\nSet BET to 0 to exit slots.\nWARNING! Placing the bet will automatically start the spin.\n";
	double bet;
	int enableDoubling = loadSlotsSettingsDSS();

	int** slotsResult = new int*[3];
	for (int i = 0; i < 3; i++)
		slotsResult[i] = new int[3];

	while (credit) {
		bet = setBet(credit);
		credit -= bet;
		if (bet == 0)
			break;

		generateSlotsResult(slotsResult);
		reviewSlotsResult(slotsResult);
		checkSlotsResult(slotsResult, credit, bet, enableDoubling);
		jackpot(bet, credit);
		// level up B
		addLevel(bet, credit);
		slotsRounds++;

	}

	for (int i = 0; i < 3; i++)
		delete[] slotsResult[i];
	delete[] slotsResult;

}

void generateSlotsResult(int **slotsResult) {
	int counter = 0;
	int counting = 11110;
	//int generatedValue;
	int row = 0;
	int column = 0;
	for (int i = 0; i < 99999; i++) {
		if (i == counting) {
			counting += 11110;
			//slotsResult[column][row] = rand() % 31;
			//slotsResult[column][row] = rand() % 21;
			slotsResult[column][row] = rand() % 101;
			if (row == 2) {
				column++;
				row = 0;
			}
			else {
				row++;
			}
		}
	}
}

void reviewSlotsResult(int** slotsResult) {
	// 1 = x2, 2 = x2, 3 = x4, 4 = x8, 0 = x20
	// 1,2 = x2, 3 = x4, 4 = x8, 5 = x20, 0 = x50 [NEW]

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (slotsResult[i][j] >= 2 && slotsResult[i][j] <= 30) {
				slotsResult[i][j] = 1;
			}
			else if (slotsResult[i][j] >= 32 && slotsResult[i][j] <= 60) {
				slotsResult[i][j] = 2;
			}
			else if (slotsResult[i][j] >= 61 && slotsResult[i][j] <= 80) {
				slotsResult[i][j] = 3;
			}
			else if (slotsResult[i][j] >= 81 && slotsResult[i][j] <= 95) {
				slotsResult[i][j] = 4;
			}
			else if (slotsResult[i][j] >= 96 && slotsResult[i][j] <= 100) {
				slotsResult[i][j] = 5;
			}
			else if (slotsResult[i][j] == 1 || slotsResult[i][j] == 31) {
				slotsResult[i][j] = 0;
			}



		}
		
	}
	cout << "\n\n\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << slotsResult[i][j] << " ";
		}
		cout << "\n";
	}
}

void checkSlotsResult(int** slotsResult, double& credit, double bet, int enableDoubling) {


	double winnings = 0;
	//new [beta]
	double criteria = 0;

	if ((slotsResult[0][0] == slotsResult[0][1]) && (slotsResult[0][0] == slotsResult[0][2])) {
		checkSlotsWin(slotsResult[0][1], bet, winnings, criteria);
	}
	if ((slotsResult[1][0] == slotsResult[1][1]) && (slotsResult[1][0] == slotsResult[1][2])) {
		checkSlotsWin(slotsResult[1][0], bet, winnings, criteria);
		
	}
	if ((slotsResult[2][0] == slotsResult[2][1]) && (slotsResult[2][0] == slotsResult[2][2])) {
		checkSlotsWin(slotsResult[2][1], bet, winnings, criteria);
		
	}

	if ((slotsResult[0][0] == slotsResult[1][1]) && (slotsResult[0][0] == slotsResult[2][2])) {
		checkSlotsWin(slotsResult[0][0], bet, winnings, criteria);
		
	}
	if ((slotsResult[2][0] == slotsResult[1][1]) && (slotsResult[2][0] == slotsResult[0][2])) {
		checkSlotsWin(slotsResult[2][0], bet, winnings, criteria);
		
	}



	if (winnings > 0 && enableDoubling) {

		cout << "\nYou won " << winnings << " CREDITS!\n";
		cout << "Do you want to double the winnings? (0 for NO, 1 for YES): ";
		int choice, numarDublaje = 0;
		cin >> choice;
		while(choice && winnings) {
			if (choice == 1) {
				int doubleResult = rand() % 2;
				if (doubleResult == 1) {
					winnings = winnings * 2;
					cout << "\nDOUBLED!\n";
					numarDublaje++;
				}
				else {
					winnings = 0;
					choice = 0;
					cout << "\nLOST!\n";
					break;
				}
			}
			if (numarDublaje == 5) {
				cout << "\nCongratulations, you reached the maximum number of doubling!\n";
				break;
			}
			cout << "\nYou won " << winnings << " CREDITS!\n";
			cout << "Do you want to continue doubling? (0 for NO, 1 for YES): ";
			cin >> choice;
		}

	}

	credit += winnings;
	if (winnings > 0) {
		cout << "\nYou won " << winnings << " CREDITS!\n";
		cout << "You have " << credit << " remaining CREDITS\n";
	}
	else {
		cout << "\nYou lost " << bet << " CREDITS!\n";
		cout << "You have " << credit << " remaining CREDITS\n";
	}
	winnings = 0;
}

void checkSlotsWin(int value, double bet, double& winnings, double &criteria) {

	if (criteria <= 3)
		criteria++;
	if (value == 1 || value == 2)
		winnings = winnings + bet * 2.5 * criteria;
	if (value == 3)
		winnings = winnings + bet * 5 * criteria;
	if (value == 4)
		winnings = winnings + bet * 10 * criteria;
	if (value == 5)
		winnings = winnings + bet * 25 * criteria;
	if (value == 0)
		winnings = winnings + bet * 100 * criteria;
		

}

int loadSlotsSettingsDSS() {
	string username = getUsername();
	ifstream getSetting("accounts/" + username + "_dss.txt");
	int enable;
	getSetting >> enable;
	return enable;
}