#include "ShopMenu.h"

ShopMenu::ShopMenu()
{
	profile = profile->GetInstance();
}

void ShopMenu::ShowMenu()
{
	int action;
	gamePlay = true;
	
	Info();

	while (gamePlay) {

		std::cout << "\nItem(101 for info): ";
		std::cin >> action;

		switch (action) {

		case 0:
			gamePlay = false;
			break;
		case 1:
			sm.IncreaseBetLimit();
			break;
		case 101:
			Info();
			break;
		default:
			Info();
			break;
		}

	}
}

void ShopMenu::Info()
{
	std::cout << "\n\n#################### Shop ####################\n\n";
	std::cout << "Username: " << profile->GetUsername() << "\n";
	std::cout << "Credit: " << profile->GetCredit() << "\n\n";

	std::cout << "Press 0 to return to main menu.\n";
	std::cout << "Press 1 to increase BET limit (MaxBet).\n";
	std::cout << "Press 101 to show this menu.\n";

	std::cout << "\n#################### Shop ####################\n\n";
}
