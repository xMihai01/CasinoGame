#include "GameMenu.h"

//Profile* Profile::instance = nullptr;

GameMenu::GameMenu() {
	profile = profile->GetInstance();
	gamePlay = true;
	Welcome();
}

void GameMenu::ShowMenu() {

	while (gamePlay && profile->GetCredit() >0) {

		std::cout << "Game (-1 for info): ";
		int alg;
		std::cin >> alg;

		switch (alg) {
		case 1:
			lotto.runGame();
			profile->ShowProfile();
			break;
		case 2:
			d.runGame();
			profile->ShowProfile();
			break;
		case 3:
			r.runGame();
			profile->ShowProfile();
			break;
		case 4:
			slot.runGame();
			profile->ShowProfile();
			break;
		case 5:
			bj.runGame();
			profile->ShowProfile();
			break;
		case 6:
			cr.runGame();
			profile->ShowProfile();
			break;
		case 0:
			profile->UpdateProfile();
			gamePlay = false;
			break;
		case 99:
			settingsMenu.ShowMenu();
			break;
		case 100:
			tMenu.ShowMenu();
			profile->ShowProfile();
			break;
		case 101:
			sMenu.ShowMenu();
			profile->ShowProfile();
			break;
		default:
			Info();
			break;
		}

		if (profile->GetLogInStatus() == false) {
			profile->DeleteInstance();
			profile->GetInstance();
			continue;
		}

		profile->UpdateProfile();
	}

	if (profile->GetCredit() <= 0) {
		std::cout << "You have no credits left!\nRestart the game and make a new account in order to keep playing!\n\n";
		profile->UpdateProfile();
		system("PAUSE");
		return;
	}

	std::cout << "\n\nThe game has stopped and everything was successfully saved!\n\n";
	system("PAUSE");

	return;

}

void GameMenu::Welcome() {

	std::cout << "#################### CasinoGame ####################\n\n";
	std::cout << "Version: 0.11" << "\n\n";

	std::cout << "Username: " << profile->GetUsername() << " \n";
	std::cout << "Level: " << profile->GetLevel()->GetLevelNumber() << "\n";
	std::cout << "CREDIT: " << profile->GetCredit() << " \n\n";


	std::cout << "Available games: Lotto(1), Doubling(2), Roulette(3), Slots(4), Blackjack(5),\n";
	std::cout << "                 Craps(6), SETTINGS(99), TOURNAMENTS(100), SHOP(101)\n\n";

	std::cout << "#################### CasinoGame ####################\n\n";
}

void GameMenu::Info() {

	std::cout << "\n\n#################### CasinoInfo ####################\n\n";

	std::cout << "Press 0 to exit.\n";
	std::cout << "Press 1 to play Lotto.\n";
	std::cout << "Press 2 to play Doubling.\n";
	std::cout << "Press 3 to play Roulette.\n";
	std::cout << "Press 4 to play Slots.\n";
	std::cout << "Press 5 to play Blackjack.\n";
	std::cout << "Press 6 to play Craps.\n";
	std::cout << "Press 99 to access Settings.\n";
	std::cout << "Press 100 to join the TournamentHall.\n";
	std::cout << "Press 101 to go Shopping.\n\n";

	std::cout << "#################### CasinoInfo ####################\n\n";
}