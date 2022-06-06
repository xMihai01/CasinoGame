#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

double setBet(double credit);
void generatetslotsResult(int** tslotsResult);
void reviewtslotsResult(int** tslotsResult, bool isBot);
void checktslotsResult(int** tslotsResult, double bet, double& points, bool isBot, int spins, int enableDoubling);
void checktSlotsWin(int value, double bet, double& winnings, double& criteria);
void jackpot(double bet, double& credit);
void matchTournamentSlotsSummary(string status, double enemyPoints, double playerPoints, int tournamentRounds);

void tournamentsSummary(string status, double credit, double bet); // From tournamentBlackjack
string getRoundStatus(int tournamentMatch); // From tournamentBlackjack 
int loadSlotsSettingsDSS();// from SLOTS
void addLevel(double bet, double& credit);

void tournamentSlots(double& credit, int& tslotsRounds, int& tslotsWins) {

	cout << "\nSet BET to 0 to exit Slots Tournament.\n";
	double tournamentBet = setBet(credit); cout << endl;
	double bet = 1;
	bool keepGoing = true;
	int enableDoubling = loadSlotsSettingsDSS();

	int tournamentRounds = 0;
	double playerPoints = 0;
	double enemyPoints = 0;

	int** tslotsResult = new int* [3];
	for (int i = 0; i < 3; i++)
		tslotsResult[i] = new int[3];

	while ((keepGoing && tournamentBet!=0) && tournamentRounds<=5) {
		
		playerPoints = 0; enemyPoints = 0;
		tournamentRounds++;
		cout << "ROUND: " << getRoundStatus(tournamentRounds);
	
		for (int i = 0; i < 50; i++) {
			
			generatetslotsResult(tslotsResult);
			reviewtslotsResult(tslotsResult, true);
			checktslotsResult(tslotsResult, bet, enemyPoints, true, i, enableDoubling);
		
		}
		if (enemyPoints >= 0 && enemyPoints <= 40)
			enemyPoints -= 5;
		else if (enemyPoints > 40 && enemyPoints <= 50)
			enemyPoints -= 7.5;
		else if (enemyPoints > 50 && enemyPoints <= 60)
			enemyPoints -= 10;
		else if (enemyPoints > 60 && enemyPoints <= 70)
			enemyPoints -= 12.5;
		else if (enemyPoints > 70 && enemyPoints <= 80)
			enemyPoints -= 15;
		else
			enemyPoints -= 20;
		

		for (int i = 0; i < 50; i++) {
			generatetslotsResult(tslotsResult);
			reviewtslotsResult(tslotsResult, false);
			checktslotsResult(tslotsResult, bet, playerPoints, false, i, enableDoubling);
		}

		
		if (playerPoints > enemyPoints) {
			//win
			matchTournamentSlotsSummary("WIN", enemyPoints, playerPoints, tournamentRounds);
			if (tournamentRounds == 5) {
				//win tourney
				credit += tournamentBet*29;
				tournamentsSummary("WIN", credit, tournamentBet);
				tslotsRounds++;
				tslotsWins++;
				jackpot(tournamentBet, credit);
				addLevel(bet*16, credit);
				break;
			}

		}
		else if (playerPoints < enemyPoints) {
			//lose
			matchTournamentSlotsSummary("LOSE", enemyPoints, playerPoints, tournamentRounds);
			credit -= tournamentBet;
			tournamentsSummary("LOSE", credit, tournamentBet);
			tslotsRounds++;
			jackpot(tournamentBet, credit);
			addLevel(bet, credit);
			break;
		}
		else if (playerPoints == enemyPoints) {
			//tie
			matchTournamentSlotsSummary("TIED", enemyPoints, playerPoints, tournamentRounds);
			tournamentRounds--;
		}

	}

	

	for (int i = 0; i < 3; i++)
		delete[] tslotsResult[i];
	delete[] tslotsResult;

}

void generatetslotsResult(int** tslotsResult) {
	int counter = 0;
	int counting = 11110;
	int row = 0;
	int column = 0;
	for (int i = 0; i < 99999; i++) {
		if (i == counting) {
			counting += 11110;
			tslotsResult[column][row] = rand() % 101;
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

void reviewtslotsResult(int** tslotsResult, bool isBot) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {


			if (tslotsResult[i][j] >= 2 && tslotsResult[i][j] <= 30) {
				tslotsResult[i][j] = 1;
			}
			else if (tslotsResult[i][j] >= 32 && tslotsResult[i][j] <= 60) {
				tslotsResult[i][j] = 2;
			}
			else if (tslotsResult[i][j] >= 61 && tslotsResult[i][j] <= 80) {
				tslotsResult[i][j] = 3;
			}
			else if (tslotsResult[i][j] >= 81 && tslotsResult[i][j] <= 95) {
				tslotsResult[i][j] = 4;
			}
			else if (tslotsResult[i][j] >= 96 && tslotsResult[i][j] <= 100) {
				tslotsResult[i][j] = 5;
			}
			else if (tslotsResult[i][j] == 1 || tslotsResult[i][j] == 31) {
				tslotsResult[i][j] = 0;
			}



		}

	}
	if (!isBot) {
		cout << "\n\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << tslotsResult[i][j] << " ";
			}
			cout << "\n";
		}
	}
}

void checktslotsResult(int** tslotsResult, double bet, double& points, bool isBot, int spins, int enableDoubling) {


	double winnings = 0;
	double criteria = 0;

	if ((tslotsResult[0][0] == tslotsResult[0][1]) && (tslotsResult[0][0] == tslotsResult[0][2])) {
		checktSlotsWin(tslotsResult[0][1], bet, winnings, criteria);
	
	}
	if ((tslotsResult[1][0] == tslotsResult[1][1]) && (tslotsResult[1][0] == tslotsResult[1][2])) {
		checktSlotsWin(tslotsResult[1][0], bet, winnings, criteria);
	
	}
	if ((tslotsResult[2][0] == tslotsResult[2][1]) && (tslotsResult[2][0] == tslotsResult[2][2])) {
		checktSlotsWin(tslotsResult[2][1], bet, winnings, criteria);
	
	}

	if ((tslotsResult[0][0] == tslotsResult[1][1]) && (tslotsResult[0][0] == tslotsResult[2][2])) {
		checktSlotsWin(tslotsResult[0][0], bet, winnings, criteria);
		
	}
	if ((tslotsResult[2][0] == tslotsResult[1][1]) && (tslotsResult[2][0] == tslotsResult[0][2])) {
		checktSlotsWin(tslotsResult[2][0], bet, winnings, criteria);
	
	}

	

	if (winnings == 0 && !isBot) {
		cout << "\nLOST\nYou have " << 49-spins << " remaining spins!\n";
		system("PAUSE");
		cout << "\n";
	}

	if ((winnings > 0 && !isBot) && enableDoubling) {

		cout << "\nYou won " << winnings << " points!\n";
		cout << "Do you want to double the winnings? (0 for NO, 1 for YES): ";
		int choice, numarDublaje = 0;
		cin >> choice;
		while (choice && winnings) {
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
					cout << "\nLOST!\n\n";
					break;
				}
			}
			if (numarDublaje == 5) {
				cout << "\nCongratulations, you reached the maximum number of doubling!\n";
				break;
			}
			cout << "\nYou won " << winnings << " points!\n";
			cout << "Do you want to continue doubling? (0 for NO, 1 for YES): ";
			cin >> choice;
		}
	}

	points += winnings;
	if (winnings > 0 && !isBot) {
		cout << "\nYou earned " << winnings << " points!\n";
		cout << "You now have " << points << " points.\n\n";
		cout << "You have " << 49 - spins << " remaining spins!\n";
		system("PAUSE");
		cout << "\n";
	}

}

void checktSlotsWin(int value, double bet, double& winnings, double& criteria) {

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

void matchTournamentSlotsSummary(string status, double enemyPoints, double playerPoints, int tournamentRounds) {

	cout << "\n\n################################# GameSummary #################################\n\n";

	cout << "Status: " << status;

	cout << "\n\nEnemy points: " << enemyPoints;
	cout << "\nYour points: " << playerPoints;

	cout << "\n\nRound: " << getRoundStatus(tournamentRounds);

	cout << "\n\n################################# GameSummary #################################\n\n";
	system("PAUSE");

}


