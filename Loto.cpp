#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

using namespace std;

double setCredit();
double setBet(double credit);
string getUsername();

void setChoices(int* choices);
bool validateChoices(int* choices, int number, int position);
void setWinningNumbers(int* winningNumbers);
bool validateWinningNumbers(int* winningNumbers, int number, int position);
int checkWin(int* winningNumbers, int* choices);
void roundSummary(int* winningNumbers, int* choices, int* foundNumber, int foundNumbers, string status, double bet, double credit);
void setFoundNumber(int* foundNumber, int* winningNumbers, int* choices, int& foundNumbers);
int loadLotoSettingsRFN();
void jackpot(double bet, double& credit);
void addLevel(double bet, double& credit);

int main();

void loto(double& credit, int &lotoRounds) {


	int* winningNumbers = new int[7];
	int* choices = new int[6];
	int* foundNumber = new int[6];

	cout << "\n\nPlace bet to 0 to exit LOTO.\n\n";
	while (credit) {
		cout << "\n";

		double bet = setBet(credit);
		if (bet == 0)
			break;
		setChoices(choices);
		
		lotoRounds++;
		setWinningNumbers(winningNumbers);
		cout << "Winning numbers are: ";
		for (int i = 0; i < 6; i++) {
			cout << winningNumbers[i] << " ";
		}

		int foundNumbers = 0;
		setFoundNumber(foundNumber, winningNumbers, choices, foundNumbers);

		if (foundNumbers >= loadLotoSettingsRFN()) {
			credit += bet * pow(4, foundNumbers);
			roundSummary(winningNumbers, choices, foundNumber, foundNumbers, "WIN", bet, credit);
		}
		else {
			credit -= bet;
			roundSummary(winningNumbers, choices, foundNumber, foundNumbers, "LOSE", bet, credit);
			
		}
		jackpot(bet, credit);
		addLevel(bet, credit);
		for (int i = 0; i < 6; i++) {
			choices[i] = 0;
		}
	}

	delete[] winningNumbers;
	delete[] choices;
	delete[] foundNumber;
	
}


void setChoices(int* choices) {
	int number;
	for (int i = 0; i < 6; i++) {
		cout << "Number " << i + 1 << ": ";
		cin >> number;
		if (validateChoices(choices, number, i)) {
			choices[i] = number;
		}
		else {
			cout << "\nERROR: The number is already a choice, negative or higher than 49.\nRetrying...\n\n";
			i--;
		}
	}
}

bool validateChoices(int* choices, int number, int position) {
	for (int i = 0; i <= position; i++) {
		if (choices[i] == number || number <= 0 || number > 49) {
			return false;
		}
	}
	return true;
}

void setWinningNumbers(int* winningNumbers) {
	int generatedNumber;
	int counter = 0;
	int passingV = 1500000;
	for (int i = 0; i < 10000000; i++) {
		if (i == passingV) {
			generatedNumber = (rand() % 49) + 1;
			if (validateWinningNumbers(winningNumbers, generatedNumber, counter)) {
				winningNumbers[counter] = generatedNumber;
				counter++;
				passingV += 1400000;
			}
			else {
				i--;
			}
		}
	}
}

bool validateWinningNumbers(int* winningNumbers, int number, int position) {
	for (int i = 0; i <= position; i++) {
		if (winningNumbers[i] == number) {
			return false;
		}
	}
	return true;
}

int checkWin(int* winningNumbers, int* choices) {
	int counter = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (choices[i] == winningNumbers[j]) {
				counter++;
			}
		}
	}
	return counter;
}

void setFoundNumber(int* foundNumber, int* winningNumbers, int* choices, int& foundNumbers) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (choices[i] == winningNumbers[j]) {
				foundNumber[foundNumbers] = winningNumbers[j];
				foundNumbers++;
			}
		}
	}

}

int loadLotoSettingsRFN() {
	string username = getUsername();
	int requiredFoundNumbers;
	ifstream getLotoRequiredFoundNumbers("accounts/" + username + "_rfn.txt");
	getLotoRequiredFoundNumbers >> requiredFoundNumbers;
	if (requiredFoundNumbers < 1 || requiredFoundNumbers >6) {
		return 3;
	}
	return requiredFoundNumbers;
}


void roundSummary(int* winningNumbers, int* choices, int* foundNumber, int foundNumbers,
	string status, double bet, double credit) {

	cout << "\n\n################################# RoundSummary #################################\n\n";

	cout << "Status: " << status << "\n";


	cout << "\nWinning numbers: | ";
	for (int i = 0; i < 6; i++) {
		cout << winningNumbers[i] << " | ";
	} cout << "      ";

	cout << "Your choices: | ";
	for (int i = 0; i < 6; i++) {
		cout << choices[i] << " | ";
	}

	if (foundNumbers != 0) {

		cout << "\nFound numbers: | ";
		for (int i = 0; i < foundNumbers; i++) {
			cout << foundNumber[i] << " | ";
		}cout << "\n";

	}
	else if(foundNumbers == 0) {
		cout << "\nYou didn't find any numbers!\n";
	}

	if (status == "LOSE") {
		//string username = getUsername();
		//ifstream getRFN("accounts/" + username + "_rfn.txt");
		int rfn = loadLotoSettingsRFN();
		//getRFN >> rfn;
		cout << "\nYou must find " << rfn << " numbers in order to win "<<"\n\nYou lost " << bet << " credits.";
		cout << "\nRemaining CREDIT: " << credit;

	}
	else {
		cout << "\nYou found " << foundNumbers << " numbers!\n\nYou won " << bet * pow(4, foundNumbers) << " credits!";
		cout << "\nRemaining CREDIT: " << credit;
	}


	cout << "\n\n################################# RoundSummary #################################\n\n";

}