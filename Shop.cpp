#include <iostream>
#include <fstream>
#include <string>

std::string getUsername();
void increaseBetLimit(std::string username, double& credit);
void displayShopMenu(std::string username, double& credit);
int getMaxBet(int itemlevel);
double getMaxBetUpgrade(int itemlevel);

void shopMenu(double& credit) {

	std::string username = getUsername();

	int action;
	bool keepGoing = true;

	displayShopMenu(username, credit);

	while (keepGoing) {

		std::cout << "\nItem(101 for info): ";
		std::cin >> action;

		switch (action) {

		case 0:
			keepGoing = false;
			break;
		case 1:
			increaseBetLimit(username, credit);
			break;
		case 101:
			displayShopMenu(username, credit);
			break;
		default:
			break;
		}

	}

}

void increaseBetLimit(std::string username, double& credit) {

	std::ifstream getLevel("userdata/" + username + "_maxbet.txt");
	int itemlevel;
	getLevel >> itemlevel;
	double upgradeCost = getMaxBetUpgrade(itemlevel);

	if (upgradeCost == -1) {
		std::cout << "\nMaxBET is at MAX level!\n";
		return;
	}


	std::cout << "\nItem: BET limit (MAX BET)\n";
	std::cout << "Item level: " << itemlevel << " --> " << itemlevel + 1 << "\n";
	std::cout << "Current Max BET: " << getMaxBet(itemlevel) << " --> " << getMaxBet(itemlevel+1) << "\n\n";
	std::cout << "Upgrade cost: " << upgradeCost << "\n\n";
	std::cout << "To upgrade, press 1. To cancel, press 0: ";

	int action;
	std::cin >> action;

	if (action == 1 && credit > upgradeCost ) {
		std::ofstream setLevel("userdata/" + username + "_maxbet.txt");
		setLevel << itemlevel + 1;
		std::cout << "\nYour MaxBET level has been upgraded to " << itemlevel + 1 << "\n\n";
		credit -= upgradeCost;
		credit += 5000;
	}
	else if (action == 1 && credit < upgradeCost) {
		std::cout << "Not enough credit! You need " << upgradeCost - credit << " more CREDIT\n";
	}
}


void displayShopMenu(std::string username, double& credit) {

	std::cout << "\n\n#################### Shop ####################\n\n";
	std::cout << "Username: " << username << "\n";
	std::cout << "Credit: " << credit << "\n\n";
	
	std::cout << "Press 0 to return to main menu.\n";
	std::cout << "Press 1 to increase BET limit.\n";
	std::cout << "Press 101 to show this menu.\n";

	std::cout << "\n#################### Shop ####################\n\n";

}

double getMaxBetUpgrade(int itemlevel) {

	if (itemlevel == 1)
		return 2000;
	else if (itemlevel == 2)
		return 5000;
	else if (itemlevel == 3)
		return 20000;
	else if (itemlevel == 4)
		return 40000;
	else if (itemlevel == 5)
		return 75000;
	else if (itemlevel == 6)
		return 150000;
	else if (itemlevel == 7)
		return 500000;
	else if (itemlevel == 8)
		return 1000000;
	else if (itemlevel == 9)
		return 10000000;
	else if (itemlevel == 10)
		return 50000000;
	else if (itemlevel == 11)
		return 150000000;
	else if (itemlevel == 12)
		return 1000000000;
	else if (itemlevel == 13)
		return 5000000000;
	else if (itemlevel == 14)
		return 100000000000;
	else
		return -1;

}

int getMaxBet(int itemlevel) {

	if (itemlevel == 1)
		return 500;
	else if (itemlevel == 2)
		return 1000;
	else if (itemlevel == 3)
		return 2000;
	else if (itemlevel == 4)
		return 3500;
	else if (itemlevel == 5)
		return 5000;
	else if (itemlevel == 6)
		return 7500;
	else if (itemlevel == 7)
		return 10000;
	else if (itemlevel == 8)
		return 25000;
	else if (itemlevel == 9)
		return 50000;
	else if (itemlevel == 10)
		return 100000;
	else if (itemlevel == 11)
		return 200000;
	else if (itemlevel == 12)
		return 300000;
	else if (itemlevel == 13)
		return 500000;
	else if (itemlevel == 14)
		return 750000;
	else
		return 999999;

}