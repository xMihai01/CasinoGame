#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

double setBet(double credit);
void jackpot(double bet, double& credit);
void addLevel(double bet, double& credit);

string getColorName(int number);
bool checkIfWinner(int color, string colorName);

void ruleta(double& credit, int& ruletaRounds) {

    cout << "\n\nSet bet to 0 to exit Ruleta.\n\n";
    double bet;
    int culoare;
    int numberPicked;
    string colorName;

    while (credit) {

        bet = setBet(credit);
        if (bet == 0)
            break;
        cout << "\nColor(0 RED, 1 BLACK, 2 GREEN): ";
        cin >> culoare;
        numberPicked = rand() % 37;
        colorName = getColorName(numberPicked);
        ruletaRounds++;

        if (checkIfWinner(culoare, colorName)) {
            cout << "\nWIN!\n"; cout << "Color: " << colorName << "        Number: " << numberPicked;
            credit += bet;
            if (culoare == 2 && colorName == "GREEN")
                credit += bet * 35;
    
        }
        else {
            cout << "\nLOSE!\n"; cout << "Color: " << colorName << "        Number: " << numberPicked;
            credit -= bet;
          
        }
        
        cout << "\n\nCREDIT remaining: " << credit << "\n";
        jackpot(bet, credit);
        addLevel(bet, credit);

    }
}

string getColorName(int number) {

    if (number == 0)
        return "GREEN";
    else if (number % 2 == 0 && number != 0)
        return "RED";
    else
        return "BLACK";

    return "ERROR";
}

bool checkIfWinner(int color, string colorName) {

    if (color == 0 && colorName == "RED")
        return true;
    else if (color == 1 && colorName == "BLACK")
        return true;
    else if (color == 2 && colorName == "GREEN")
        return true;
    else
        return false;

    return false;
}