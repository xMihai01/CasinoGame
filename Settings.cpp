#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main();
string getUsername();

void showSettingsMenu(string username);
void changeLotoRequiredFoundNumbers(string username);
void changeDoublingStatus(string username);
void changePassword(string username);
void changeDoublingRandomBet(string username);
int resetAccount(string username);

void settingsMenu(int &logOut) {
	
	bool keepGoing = true;
	string username = getUsername();

	while (keepGoing) {

		showSettingsMenu(username);
		int choice;
		cout << "\nSetting: ";
		cin >> choice;

		switch (choice) {
		case 1:
			changeLotoRequiredFoundNumbers(username);
			keepGoing = false;
			break;
		case 2:
			changeDoublingStatus(username);
			keepGoing = false;
			break;
		case 3:
			changeDoublingRandomBet(username);
			keepGoing = false;
			break;
		case 10:
			changePassword(username);
			keepGoing = false;
			break;
		case 19:
			logOut = resetAccount(username);
			keepGoing = false;
			break;
		case 0:
			keepGoing = false;
			break;
		default:
			cout << "\nInvalid setting!\n";
			break;
		}


	}

}


void showSettingsMenu(string username) {

	cout << "\n#################### CasinoSettings ####################\n\n";

	cout << "Username: " << username << "\n\n";

	cout << "Press 0 to exit Settings Menu\n";
	cout << "Press 1 to change Required Found Numbers to win at LOTO\n";
	cout << "Press 2 to turn on/off doubling wins at SLOTS\n";
	cout << "Press 3 to change number of digits for a RandomDoubling bet\n";
	cout << "Press 10 to change your password\n";
	cout << "Press 19 to RESET your account\n\n";

	cout << "#################### CasinoSettings ####################\n\n";

}

void changeLotoRequiredFoundNumbers(string username) {

	ifstream getLotoRequiredFoundNumbers("accounts/" + username + "_rfn.txt");
	int aux;
	bool success = false;
	cout << "\nWARNING! The default value for this setting is 3\n";

	if (!(getLotoRequiredFoundNumbers >> aux)) {
		aux = 3;
		ofstream setLotoRequiredFoundNumbers("accounts/" + username + "_rfn.txt", ios::app);
		setLotoRequiredFoundNumbers << aux;
	}
	else {
		while (!success) {
		
			cout << "\nRequired found numbers in order to win loto: ";
			cin >> aux;
			if (aux >= 1 && aux <= 6) {
				ofstream setLotoRequiredFoundNumbers("accounts/" + username + "_rfn.txt");
				setLotoRequiredFoundNumbers << aux;
				cout << "\nThis setting has been successfully changed!\n";
				success = true;
			}
			else {
				cout << "\nAn error occurred while changing this setting\n";
				cout << "This setting only accepts values between 1 and 6\n\n";
			}
		}
	}

}

void changeDoublingStatus(string username) {

	ifstream getDoublingStatus("accounts/" + username + "_dss.txt");
	int aux;
	bool success = false;
	cout << "\nWARNING! The default value for this setting is 1 (enabled)\n";

	//for current setting
	if (!(getDoublingStatus >> aux)) {
		ofstream setSetting("accounts/" + username + "_dss.txt", ios::app);
		setSetting << 1;
	}
	else {

		while (!success) {

			cout << "\nEnable doubling at SLOTS(0 for NO, 1 for YES): ";
			cin >> aux;
			if (aux == 1 || aux == 0) {
				ofstream setSetting("accounts/" + username + "_dss.txt");
				setSetting << aux;
				cout << "\nThis setting has been successfully changed!\n";
				success = true;
			}
			else {
				cout << "\nAn error occurred while changing this setting\n";
				cout << "This setting only accepts value 0 or 1\n\n";
			}
		}

	}
}

void changeDoublingRandomBet(string username) {

	ifstream getDoublingRandomBet("accounts/"  + username + "_drb.txt");
	int aux;
	bool success = false;
	cout << "\nWARNING! The default value for this setting is 1\n";

	if (!(getDoublingRandomBet >> aux)) {
		aux = 1;
		ofstream setDoublingRandomBet("accounts/" + username + "_drb.txt", ios::app);
		setDoublingRandomBet << aux;
	}
	else {
		while (!success) {

			cout << "\nNumber of digits for a RandomDoubling bet: ";
			cin >> aux;
			if (aux >= 1 && aux <= 350) {
				ofstream setDoublingRandomBet("accounts/" + username + "_drb.txt");
				setDoublingRandomBet << aux;
				cout << "\nThis setting has been successfully changed!\n";
				success = true;
			}
			else {
				cout << "\nAn error occurred while changing this setting\n";
				cout << "This setting only accepts values between 1 and 350\n\n";
			}
		}
	}

}

void changePassword(string username) {

	ifstream getPassword("accounts/" + username + ".txt");

	string password = "";
	string inputPassword = "";
	bool keepGoing = true;

	while (keepGoing) {
		cout << "Old Password: ";
		cin >> inputPassword;
		getPassword >> password;

		if (inputPassword == password) {

			ofstream setPassword("accounts/" + username + ".txt");
			cout << "New password: ";
			cin >> inputPassword;
			setPassword << inputPassword;
			cout << "Your password has been successfully changed!\n";
			keepGoing = false;
		}
		else {
			cout << "Incorrect password! \n";

			cout << "Do you want to continue?(yes/no): ";
			string retry;
			cin >> retry;
			if (retry != "yes") {
				cout << "Oof.. okay...\n";
				keepGoing = false;
			}

		}
	}

}

int resetAccount(string username) {

	string choice;
	cout << "\n\n\n\n\n\n\n\n##################### WARNING #####################\n\nYou are about to RESET your account!\nAre you sure you want to continue? This cannot be undone!\n\n##################### WARNING#####################\n\n";
	cout << "\nContinue?(YES or NO): "; cin >> choice;

	if (choice != "YES") {
		cout << "Returning...\n";
		return 0;
	}

	fstream getPassword("accounts/" + username + ".txt");
	bool confirmed = false;

	string password = "";
	string inputPassword = "";
	bool keepGoing = true;

	cout << "\n\nPlease enter your password in order to reset your account!\n";

	while (keepGoing) {
		cout << "Password: ";
		cin >> inputPassword;
		getPassword >> password;

		if (inputPassword == password) {
			keepGoing = false;
			confirmed = true;
		}
		else {
			cout << "Incorrect password! \n";

			cout << "Do you want to continue?(yes/no): ";
			string retry;
			cin >> retry;
			if (retry != "yes") {
				cout << "Returning...\n";
				keepGoing = false;
				return 0;
			}

		}
	}

	if (confirmed) {

		string c;
		cout << "\n\n\n\n\nYOU ARE ABOUT TO RESET THIS ACCOUNT\nTHIS ACTION CANNOT BE UNDONE\n";
		cout << "Reset(YES or NO): "; cin >> c;

		if (c == "YES") {
			ofstream getGames("userdata/" + username + "_games.txt");
			ofstream getCredit("userdata/" + username + "_credit.txt");
			ofstream getCredit1("userdata/" + username + "_jackpot.txt");
			ofstream getCredit2("userdata/" + username + "_tournamentgames.txt");
			ofstream getCredit3("userdata/" + username + "_pass.txt");
			ofstream getCredit4("userdata/" + username + "_level.txt");
			ofstream getCredit5("accounts/" + username + ".txt");
			ofstream getCredit6("accounts/" + username + "_drb.txt");
			ofstream getCredit7("accounts/" + username + "_dss.txt");
			ofstream getCredit8("accounts/" + username + "_rfn.txt");
			ofstream getCredit9("userdata/" + username + "_maxbet.txt");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			cout << "Your account has been successfully reset!";
			return 1;
		}
		else {
			cout << "\nReturning...\n";
			return 0;
		}



	}
	return 0;
}
