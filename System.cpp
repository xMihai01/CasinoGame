#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include <fstream>
#include <string>

#define version "0.10b7"

using namespace std;

int main();

string username = "";
double creditNew = 0;

double setCreditNew();
void setDefaultSettings();
int getLevel();
double getEXP();
void loadLevel();

int getMaxBet(int itemlevel);

bool loggedIn() {

    _mkdir("accounts");
    _mkdir("userdata");
    bool isLogged = false;
    //string username = "";
    string password = "";
    cout << "Username: ";
    cin >> username;


    while (!isLogged) {
        ifstream getPassword("accounts/" + username + ".txt");
        if (!(getPassword >> password)) {
            cout << "There is no account matching this username.\nCreating one...\n";
            cout << "Set your password: ";
            cin >> password;
            ofstream setPassword("accounts/" + username + ".txt", ios::app);
            setPassword << password;

            setDefaultSettings();
        }
        else {
            ifstream getPassword("accounts/" + username + ".txt");
            string temp = "unknown";
            getline(getPassword, temp);
            cout << "Password: ";
            cin >> password;

            if (temp == password) {
                isLogged = true;
            }
            else {
                cout << "Incorrect password!\n";
            }
        }
    }

    cout << "Successfully logged in!\n\n";
    loadLevel();
    return true;

}

double setCreditNew() {
   
    ifstream getCredit("userdata/" + username + "_credit.txt");
    if (!(getCredit >> creditNew)) {
        cout << "Welcome to CasinoGame, " + username + ", you received 1000 CREDITS, enjoy!\n\n";
        creditNew = 1000;
        ofstream setCredit("userdata/" + username + "_credit.txt", ios::app);
    
        setCredit << creditNew;
    }
    else {
        ifstream getCredit("userdata/" + username + "_credit.txt");
        getCredit >> creditNew;
    }

   
    
    return creditNew;
}

void updateCredit(double credit) {

    if (credit < 0)
        credit = 0;

    ofstream setCredit("userdata/" + username + "_credit.txt");
    setCredit << credit;

}

void setGamesPlayed(int& lotoRounds, int& dublajeRounds, int& ruletaRounds, int& slotsRounds, int& blackjackRounds, int& barbutRounds) {

    ifstream getGames("userdata/" + username + "_games.txt");
    if (!(getGames >> lotoRounds)) {
        ofstream setGames("userdata/" + username + "_games.txt", ios::app);
        setGames << lotoRounds << "\n";
        setGames << dublajeRounds << "\n";
        setGames << ruletaRounds << "\n";
        setGames << slotsRounds << "\n";
        setGames << blackjackRounds << "\n";
        setGames << barbutRounds << "\n";

    }
    else {
        ifstream getGames("userdata/" + username + "_games.txt");
        getGames >> lotoRounds;
        getGames >> dublajeRounds;
        getGames >> ruletaRounds;
        getGames >> slotsRounds;
        getGames >> blackjackRounds;
        getGames >> barbutRounds;
    }

}

void setTournamentGames(int& tblackjackRounds, int& tblackjackWins, int& tslotsRounds, int& tslotsWins) {

    ifstream getGames("userdata/" + username + "_tournamentgames.txt");
    if (!(getGames >> tblackjackRounds)) {
        ofstream setGames("userdata/" + username + "_tournamentgames.txt", ios::app);
        setGames << tblackjackRounds << "\n";
        setGames << tblackjackWins << "\n";
        setGames << tslotsRounds << "\n";
        setGames << tslotsWins << "\n";


    }
    else {
        ifstream getGames("userdata/" + username + "_tournamentgames.txt");
        getGames >> tblackjackRounds;
        getGames >> tblackjackWins;
        getGames >> tslotsRounds;
        getGames >> tslotsWins;

    }

}

void updateGames(int lotoRounds, int dublajeRounds, int ruletaRounds, int slotsRounds, int blackjackRounds, int barbutRounds) {

    ofstream setGames("userdata/" + username + "_games.txt");
    setGames << lotoRounds << "\n" << dublajeRounds << "\n" << ruletaRounds << "\n"
        << slotsRounds << "\n" << blackjackRounds << "\n" << barbutRounds;

}

void updateTournamentGames(int tblackjackRounds, int tblackjackWins, int tslotsRounds, int tslotsWins) {

    ofstream setTournamentGames("userdata/" + username + "_tournamentgames.txt");
    setTournamentGames << tblackjackRounds << "\n" << tblackjackWins << "\n" <<
        tslotsRounds << "\n" << tslotsWins << "\n";

}


double setBet(double credit) {
	double bet, maxbet, i =1;
//	cout << "BET: ";
	//cin >> bet;

    ifstream getMaxBetFile("userdata/" + username + "_maxbet.txt");
    getMaxBetFile >> maxbet;
    maxbet = getMaxBet(maxbet);
    while (i) {
        i = 0;
        cout << "BET: ";
        cin >> bet;
        if (bet > maxbet) {
            std::cout << "\nERROR: You can't place a bet that is higher than " << maxbet;
            if (!(maxbet == 999999))
                std::cout << "\nUpgrade your max bet in the shop!\n";
            i = 1;
        }
        if (credit < bet) {
            std::cout << "\nERROR: Not enough credits to place bet.\n";
            i = 1;
        }
        else if (bet < 0) {
            std::cout << "\nERROR: Invalid bet.\n";
            i = 1;
        }
    }

	return bet;
}

void jackpot(double bet, double& credit) {

    ifstream getJackpot("userdata/" + username + "_jackpot.txt");
    double jackpot = -1;
    double randomValue = rand() % 10 + 1;
    double addedValue = randomValue / 100;
    if (!(getJackpot >> jackpot)) {

        ofstream setJackpot("userdata/" + username + "_jackpot.txt");
        setJackpot << 1;
    }
    else {
        getJackpot >> jackpot;
        ofstream setJackpot("userdata/" + username + "_jackpot.txt");
        jackpot = jackpot + (bet * addedValue);
        setJackpot << jackpot;

    }

    if (rand() % 1000 == 73) {

        getJackpot >> jackpot;
        credit += jackpot;
        cout << "\n\n##################################################################\n\n";
        cout << "Congratulations, you won the JACKPOT of " << jackpot << " CREDITS";
        cout << "\n\n##################################################################\n\n";
        ofstream setJackpot("userdata/" + username + "_jackpot.txt");
        setJackpot << 1;
        system("PAUSE");
    }

}

double setCredit() {
	double credit;
	cout << "CREDIT: ";
	cin >> credit;
	if (credit <= 0) {
		cout << "\nERROR: Negative credit values are not allowed!\nCredit has been set to 10 by default.";
		return 10;
	}
	return credit;
}


string getUsername() {
    string tempusername = username;
    return tempusername;
}


void setDefaultSettings() {

    ofstream setRfn("accounts/" + username + "_rfn.txt"); //random found numbers
    setRfn << 3;
    ofstream setDss("accounts/" + username + "_dss.txt"); //doubling status
    setDss << 1 << "\n";
    ofstream setDrb("accounts/" + username + "_drb.txt"); // random doubling digits for bet
    setDrb << 1 << "\n";

    // Shop

    ofstream setMaxBet("userdata/" + username + "_maxbet.txt");
    setMaxBet << 1;

}


void welcome() {

	cout << "#################### CasinoGame ####################\n\n";
	cout << "Version: " << version << "\n\n";

    cout << "Username: " << username << " \n";
    cout << "Level: " << getLevel() << "\n";
    cout << "CREDIT: "  << creditNew << " \n\n";
   

    cout << "Available games: Loto(1), Dublaje(2), Ruleta(3), Slots(4), Blackjack(5),\n";
    cout << "                 Barbut(6), SETTINGS(99), TOURNAMENTS(100), SHOP(101), MINIGAMES(102)\n\n";

	cout << "#################### CasinoGame ####################\n\n";
}

void info() {

	cout << "\n\n#################### CasinoInfo ####################\n\n";

	cout << "Press 0 to exit.\n";
	cout << "Press 1 to play Loto.\n";
	cout << "Press 2 to play Dublaje.\n";
	cout << "Press 3 to play Ruleta.\n";
	cout << "Press 4 to play Slots.\n";
    cout << "Press 5 to play Blackjack.\n";
    cout << "Press 6 to play Barbut.\n";
    cout << "Press 100 to join the TournamentHall.\n";
    cout << "Press 101 to go Shopping.\n";
    cout << "Press 102 to go to Minigames.\n\n";


	cout << "#################### CasinoInfo ####################\n\n";
}
